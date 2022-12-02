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

  game.showFullScreen();

  return app.exec();
}
