//#include "headers/Card.h"
//#include "headers/Monstercard.h"
#include "headers/Player.h"
#include "headers/Game.h"
//#include "headers/mainwindow.h"
#include "headers/Deck.h"
#include "headers/Card.h"
#include "headers/mainmenu.h"
#include <iostream>
#include <QApplication>
#include "headers/CardMenu.h"
#include"headers/mainmenu.h"
#include "headers/profilesettings.h"
#include "BotPlayer.h"

int main(int argc,char **argv)
{
  QApplication app(argc, argv);


  Player player1("Nikola");
  BotPlayer player2("Bot");
  MonsterCard* globalMonsterCard1 = new MonsterCard("Sibirski Plavac", 3000, 2500, 4, MonsterType::DRAGON,
                                              MonsterKind::NORMAL_MONSTER, MonsterAttribute::LIGHT,
                                              true, Position::ATTACK, false,
                                              CardType::MONSTER_CARD, CardLocation::HAND, "Opis", false
                                             );

  SpellCard* globalSpellCard = new SpellCard(SpellType::NORMAL_SPELL, "Dark Hole",
                                             CardType::SPELL_CARD, CardLocation::HAND,
                                             " Destroy all monsters on the field. ", true);
  std::vector<Card *> cards;
  cards.push_back(globalMonsterCard1);
  cards.push_back(globalSpellCard);
  Deck *d = new Deck("/", cards);
//  player1.drawCards(3);
    //MainMenu m;
      //m.show();
  player1.setDeck(*d);
  Game game(player1, player2);

  player1.drawCards(1);
  player1.drawCards(1);
  player1.drawCards(1);
//  game.showFullScreen();
   profileSettings p;
   //   p.resize(500, 500);
   p.setMinimumWidth(1024);
   p.setMinimumHeight(711);
   p.setMaximumHeight(711);
   p.setMaximumWidth(1024);
   p.show();
  return app.exec();
}
