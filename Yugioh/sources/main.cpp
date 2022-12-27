#include "headers/Player.h"
#include "headers/Game.h"
#include "headers/mainmenu.h"
#include <iostream>

#include <QApplication>
#include "headers/CardMenu.h"
#include "headers/Serializer.h"

#include "decksettings.h"

int main(int argc,char **argv)
{
  QApplication app(argc, argv);

  //MainMenu m;
  //m.showFullScreen();

  deckSettings d;
  d.show();


  app.exec();
  return 0;
}
