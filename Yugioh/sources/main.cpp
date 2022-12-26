//#include "headers/mainwindow.h"
#include "headers/mainmenu.h"
#include <iostream>

#include <QApplication>

int main(int argc,char **argv)
{
  QApplication app(argc, argv);

  MainMenu m;
  m.showFullScreen();

  return app.exec();
}
