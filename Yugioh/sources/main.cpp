//#include "headers/Card.h"
//#include "headers/Monstercard.h"
#include "headers/Player.h"
#include "headers/Game.h"
//#include "headers/mainwindow.h"

#include <iostream>
#include <QApplication>
#include "headers/CardMenu.h"
#include"headers/mainmenu.h"
int main(int argc,char **argv)
{
  QApplication app(argc, argv);

  //Player player1("Nikola");
  //Player player2("Milan");

  //Game game(player1, player2);
  //game.show();

  MainMenu m;
  m.show();

  // FIXME: This loop can't exist, because we need app.exec() (Qt's event loop)
//  game.start();
//    game.show(); //this is to turn on the graphics, need to decide if we use Game as pointer

//  MainWindow w;
//  w.show();

//MonsterCard::MonsterCard(int attackPoints, int defensePoints, MonsterType tip,MonsterKind kind,
//  Attribute atribut, int level, const std::string &CardName, CardType CType, CardPlace CPlace, const std::string &CardDescription)

  // MonsterCard card(3000, 2500,
  //                  MonsterType::DRAGON, MonsterKind::NORMAL_MONSTER, MonsterAttribute::LIGHT,
  //                  8, "Sibirski Plavac", CardType::MONSTER_CARD, CardLocation::HAND, "Placeholder Description"
  //                  );
  // std::cout << card.getHeight() << std::endl;



  // CardMenu cardmenu(&card);
  // cardmenu.setGeometry(0,0,card.getWidth(),card.getHeight());
  // cardmenu.setGeometry(card.boundingRect());
  // card.boundingRect();
  // cardmenu.show();


  app.exec();
  return 0;
}
