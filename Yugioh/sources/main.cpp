//#include "headers/Card.h"
//#include "headers/Monstercard.h"
#include "headers/Player.h"
#include "headers/Game.h"
//#include "headers/mainwindow.h"
#include "headers/mainmenu.h"
#include <iostream>
#include <QApplication>
#include "headers/CardMenu.h"
#include "headers/Serializer.h"

int main(int argc,char **argv)
{
  QApplication app(argc, argv);

  Serializer s;
  s.loadFromJson(":/resources/kaiba.json");
  for(auto card : s.getCards())
    qWarning() << card;

  //  MainMenu m;
  //  m.showFullScreen();

  app.exec();
  return 0;
}
