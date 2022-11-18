#include "headers/Card.h"
#include "headers/Player.h"
#include "headers/Game.h"
#include <iostream>
#include <QApplication>

int main(int argc,char **argv)
{
   QApplication app(argc,argv);

  Player player1("Nikola");
  Player player2("Milan");

  Game game(player1, player2);
  game.start();
  //game->show(); this is to turn on the graphics, need to decide if we use Game as pointer



  Card karta("Dark magician",CardType::MonsterCard,CardPlace::Grave,"opis");
  std::cout << karta << std::endl;

  app.exec();
  return 0;
}
