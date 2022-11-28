//#include "headers/Card.h"
//#include "headers/Monstercard.h"
#include "headers/Player.h"
#include "headers/Game.h"
//#include "headers/mainwindow.h"

#include <iostream>
#include <QApplication>

int main(int argc,char **argv)
{
  QApplication app(argc, argv);

  Player player1("Nikola");
  Player player2("Milan");

  Game game(player1, player2);
  game.show();

  // FIXME: This loop can't exist, because we need app.exec() (Qt's event loop)
//  game.start();
//    game.show(); //this is to turn on the graphics, need to decide if we use Game as pointer

//  MainWindow w;
//  w.show();

  return app.exec();
}
