//#include "headers/Card.h"
//#include "headers/Monstercard.h"
#include "headers/Player.h"
#include "headers/Game.h"
//#include "headers/mainwindow.h"
#include "headers/Deck.h"
#include "headers/Card.h"
#include <iostream>
#include <QApplication>
#include "headers/CardMenu.h"
#include"headers/mainmenu.h"
int main(int argc,char **argv)
{
  QApplication app(argc, argv);


  Player player1("Nikola");
  Player player2("Milan");
//  player1.drawCards(3);
    //MainMenu m;
      //m.show();


  Game game(player1, player2);

  game.showFullScreen();

  return app.exec();
}
