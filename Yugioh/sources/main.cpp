#include "headers/Player.h"
#include "headers/Game.h"
#include "headers/mainmenu.h"
#include <iostream>
#include <QApplication>
#include "headers/CardMenu.h"

int main(int argc,char **argv)
{
  QApplication app(argc, argv);

  MainMenu m;
  m.showFullScreen();

  app.exec();
  return 0;
}
