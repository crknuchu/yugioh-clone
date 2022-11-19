#include "headers/Card.h"
#include "headers/Monstercard.h"
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
//  game.start();
  //game->show(); this is to turn on the graphics, need to decide if we use Game as pointer


//MonsterCard::MonsterCard(int attackPoints, int defensePoints, MonsterType tip,MonsterKind kind,
//  Attribute atribut, int level, const std::string &CardName, CardType CType, CardPlace CPlace, const std::string &CardDescription)

  MonsterCard card(3000, 2500,
                   MonsterType::DRAGON, MonsterKind::NORMAL_MONSTER, MonsterAttribute::LIGHT,
                   8, "Sibirski Plavac", CardType::MONSTER_CARD, CardLocation::HAND, "Placeholder Description"
                   );
  std::cout << card << std::endl;

  app.exec();
  return 0;
}
