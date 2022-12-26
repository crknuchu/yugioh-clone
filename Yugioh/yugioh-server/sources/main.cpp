#include <QApplication>

#include "headers/MyTcpServer.h"

int main(int argc, char **argv) {
  QApplication app(argc, argv);
  MyTcpServer server;

//  if(!server.listen(QHostAddress::LocalHost, 8090))
//      return -1;

  QHostAddress addr(QString::fromStdString("localhost"));

  if(!server.listen(addr, 8090))
      return -1;

  return app.exec();
}
