#ifndef MYTCPSERVER_H
#define MYTCPSERVER_H

#include <QObject>
#include <QTcpServer>
#include <QHostAddress>
#include <QDataStream>
#include <map>

class MyTcpServer : public QObject {
    Q_OBJECT

public:
    MyTcpServer(QObject  *parent = nullptr);
    ~MyTcpServer();
    bool listen(const QHostAddress &ip = QHostAddress::Any, quint16 port = 0);
private:
    QTcpServer *m_pServer = nullptr;
    std::map<QTcpSocket *, int> m_clients;
    int m_numOfClients = 0; // static?

    // TODO: use std::map
    QHash<QTcpSocket *, QByteArray *> m_buffers; // We need a buffer to store data until block has beencompletely received
    QHash<QTcpSocket *, qint32 *> m_sizes; // We need to store the size to verify if a block has been received completely

    // Private member functions
    qint32 QByteArrayToQInt32(QByteArray array);
    int randomGenerator(const int limit) const;

    // Stuff that needs to be same for both players in the game so we do it here before the game start
    int decideWhoPlaysFirst() const;


private slots:
    void onNewConnection();
    void onDataIncoming();
    void onDataReceived(QByteArray &receivedData, QTcpSocket *pSenderSocket); // const?
    void onClientDisconnect();

signals:
    void dataReceived(QByteArray &data, QTcpSocket *pSenderSocket); // const?



};

#endif // MYTCPSERVER_H
