#include "headers/Player.h"
#include "headers/Game.h"
#include "headers/mainmenu.h"
#include <iostream>
#include <QApplication>
#include "headers/CardMenu.h"
#include "headers/Serializer.h"

int main(int argc,char **argv)
{
  QApplication app(argc, argv);

  Serializer s;
  s.loadFromJson(":/resources/yugi.json");
  for(auto card : s.getCards())
    qWarning() <<  QString::fromStdString(card->getCardName());

    //MainMenu m;
    //m.showFullScreen();

  app.exec();
  return 0;
}
