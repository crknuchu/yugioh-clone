#include "headers/MyTcpServer.h"

#include <iostream>
#include <random>
#include <QTcpSocket>
#include <QDataStream>

MyTcpServer::MyTcpServer(QObject *parent)
    : QObject(parent),
    m_pServer(new QTcpServer(this))
{
    connect(m_pServer, &QTcpServer::newConnection, this, &MyTcpServer::onNewConnection); // Connect the handleNewConnection slot to signal.
}

MyTcpServer::~MyTcpServer() {
    delete m_pServer;
}


bool MyTcpServer::listen(const QHostAddress &ip, quint16 port)
{
    std::cout << "The server is listening at port..." << port << std::endl;
    return m_pServer->listen(ip, port);
}

void MyTcpServer:: onNewConnection()
{
    while(m_pServer->hasPendingConnections())
    {
        std::cout << "We have a new connection!" << std::endl;

        // SERVER ------|clientSocket|------- CLIENT
        // Both sides can read and write to this single socket.
        QTcpSocket *clientSocket = m_pServer->nextPendingConnection();
        connect(clientSocket, &QIODevice::readyRead, this, &MyTcpServer::onDataIncoming); // Qt::UniqueConnection?
        connect(this, &MyTcpServer::dataReceived, this, &MyTcpServer::onDataReceived, Qt::UniqueConnection);
        connect(clientSocket, &QAbstractSocket::disconnected, this, &MyTcpServer::onClientDisconnect);


        // Add the client to the vector of clients:
        m_clients[clientSocket] = ++m_numOfClients;

        // Initialize  the QHash map fields with default values
        QByteArray *pBuffer = new QByteArray();
        qint32 *pSize = new qint32(0);
        m_buffers.insert(clientSocket, pBuffer);
        m_sizes.insert(clientSocket, pSize);

        // We want to start the game only when 2 clients connect to the server
        if(m_numOfClients == 2)
        {
            std::cout << "Number of clients is 2, the game should start soon..." << std::endl;

            // Decide who plays first
            int whoPlaysFirst = decideWhoPlaysFirst();
            for(std::pair<QTcpSocket*, int> clientSocket : m_clients)
            {
                // We also send the id to each Game client so it knows about itself.
                std::cout << "Id in loop: " << clientSocket.second << std::endl;

                QByteArray buffer;
                QDataStream outDataStream(&buffer, QIODevice::WriteOnly);
                outDataStream.setVersion(QDataStream::Qt_5_15);
                outDataStream << QString::fromStdString("START_GAME") // Notify clients that the game should start
                              << qint32(whoPlaysFirst)// Tell them who plays first
                              << qint32(clientSocket.second); // Tell them who they are
                clientSocket.first->write(buffer);
            }
        }
    }
}

void MyTcpServer::onClientDisconnect()
{
    std::cout << "We are in onDisconnect" << std::endl;
    QTcpSocket *socket = static_cast<QTcpSocket*>(sender()); // sender is the QObject that emitted the signal that triggers this slot
    QByteArray *buffer = m_buffers.value(socket);
    qint32 *s = m_sizes.value(socket);

    m_clients.erase(socket);
    m_numOfClients--;

    socket->deleteLater();
    delete buffer;
    delete s;

    // If the number of clients reached 0 (the game ended and they disconnected), stop the server too
//    if(m_numOfClients == 0)
//        m_pServer->close();
}


void MyTcpServer::onDataIncoming() {
    std::cout << "We are in data incoming slot" << std::endl;

    QTcpSocket *pSocket = static_cast<QTcpSocket*>(sender());
    std::cout << "The one who sent data is client with id " << m_clients[pSocket] << std::endl;

    QByteArray *pBuffer = m_buffers.value(pSocket);
    qint32 *s = m_sizes.value(pSocket);
    qint32 size = *s;

    std::cout << "Size: " << size << std::endl;


    // pBuffer = size | data
    while(pSocket->bytesAvailable() > 0) // Check if there are any bytes awaiting to be read
    {
        // Append the byte array returned by readAll to our buffer
        pBuffer->append(pSocket->readAll());

        // TODO (check): This while loop should ensure that we read the complete data
        while((size == 0 && pBuffer->size() >= 4) || (size > 0 && pBuffer->size() >= size)) //While we can process data, process it
        {
            if (size == 0 && pBuffer->size() >= 4) // If the data's size has been received completely, we store it
            {
                // QByteArray::mid(pos, len) returns a byte array with length `len` starting from position `pos`
                size = QByteArrayToQInt32(pBuffer->mid(0, 4));
                *s = size;
                pBuffer->remove(0, 4);
            }

            if (size > 0 && pBuffer->size() >= size) // If the data has been received completely, we store it
            {
                QByteArray data = pBuffer->mid(0, size);
                pBuffer->remove(0, size);
                size = 0;
                *s = size;
                emit dataReceived(data, pSocket);
            }
        }
    }
}


// TODO: Check if dataReceived signal needs to be connected to this slot by using queued connection
void MyTcpServer::onDataReceived(QByteArray &receivedData, QTcpSocket *pSenderSocket)
{
    std::cout << "We are in onDataReceived" << std::endl;
    std::cout << "Data received: " << receivedData.toStdString() << std::endl;

    std::cout << "Number of clients: " << m_numOfClients << std::endl;

    // The data we receive from one client needs to be relayed to the other clients too
    for(std::pair<QTcpSocket*, int> clientSocket : m_clients)
    {
        std::cout << "ClientSocket id : " << clientSocket.second << std::endl;
        // Send the received data to all other clients
        if(clientSocket.first != pSenderSocket)
        {
            clientSocket.first->write(receivedData);
        }
    }
}

// TODO: QInt vs QInt32
qint32 MyTcpServer::QByteArrayToQInt32(QByteArray source)
{
    qint32 tmp;
    QDataStream stream(&source, QIODevice::ReadWrite);
    stream >> tmp;
    return tmp;
}

int MyTcpServer::randomGenerator(const int limit) const {
  /*
   * Uniformly-distributed integer random number
   * generator that produces non-deterministic
   * random numbers.
   */
  std::random_device rd;

  /*
   *  A Mersenne Twister pseudo-random generator
   *  of 32-bit numbers with a state size of
   *  19937 bits.
   */
  std::mt19937 gen(rd());

  // Uniform distribution (from 1 to limit)
  std::uniform_int_distribution<> dis(1, limit);
  return dis(gen);
}

int MyTcpServer::decideWhoPlaysFirst() const
{
    return randomGenerator(2);
}
