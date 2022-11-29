#include "headers/Card.h"
#include "headers/Monstercard.h"
#include "headers/Spellcard.h"
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
//  std::cout << card << std::endl;

  SpellCard card2(SpellType::NORMAL_SPELL, "Dark Hole", CardType::SPELL_CARD, CardLocation::HAND, "Destroy all monsters on the field.");

  std::vector<MonsterCard*> monsterZone;

//  monsterZone.insert(monsterZone.begin(), &card);
//  monsterZone.insert(monsterZone.begin(), &card2);
    MonsterCard* c = dynamic_cast<MonsterCard*>(&card);
    MonsterCard* c1 = dynamic_cast<MonsterCard*>(&card2);
    if(c){
          monsterZone.insert(monsterZone.begin(), c);
    }
    if(c1)
        monsterZone.insert(monsterZone.begin(), c1);
//  if(typeid(card2).name())
  for(auto x : monsterZone){
      std::cout << *x << std::endl;
  }
  app.exec();
  return 0;
}
