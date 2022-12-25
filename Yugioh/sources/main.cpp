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
  s.loadFromJson(":/resources/yugi.json");
  for(auto card : s.getCards())
    qWarning() <<  QString::fromStdString(card->getCardName());

  MainMenu m;
  m.showFullScreen();

  Player player1("Nikola");
  BotPlayer player2("Bot");
  std::vector<Card*> cards = s.getCards();
  Deck d = Deck(cards);
//  player1.drawCards(3);
    //MainMenu m;
      //m.show();
  player1.setDeck(d);
  Game game(player1, player2);

  player1.drawCards(1);
  player1.drawCards(1);
  player1.drawCards(1);
  game.showFullScreen();

  return app.exec();
}
