#include "headers/Player.h"
#include "headers/Game.h"
//#include "headers/mainwindow.h"
#include "headers/Deck.h"
#include "headers/Card.h"
#include "headers/mainmenu.h"
#include <iostream>

#include <QApplication>
#include "headers/CardMenu.h"
#include "BotPlayer.h"
#include "headers/Serializer.h"

int main(int argc,char **argv)
{
  QApplication app(argc, argv);

  Serializer s;
  s.loadFromJson(":/resources/kaiba.json");
  for(auto card : s.getCards())
    qWarning() <<  QString::fromStdString(card->getCardName());

  MainMenu m;
  m.showFullScreen();

  Player player1("Nikola");
  BotPlayer player2("Bot");
  MonsterCard* globalMonsterCard1 = new MonsterCard("Sibirski Plavac", 3000, 2500, 4, MonsterType::DRAGON,
                                              MonsterKind::NORMAL_MONSTER, MonsterAttribute::LIGHT,
                                              true, Position::ATTACK, false,
                                              CardType::MONSTER_CARD, CardLocation::HAND, "Opis",":/resources/pictures/blue_eyes.jpg" ,false
                                             );

  SpellCard* globalSpellCard = new SpellCard(SpellType::NORMAL_SPELL, "Dark Hole",
                                             CardType::SPELL_CARD, CardLocation::HAND,
                                             " Destroy all monsters on the field. ", ":/resources/pictures/dark_energy.jpg", true);
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
  game.showFullScreen();

  return app.exec();
}
