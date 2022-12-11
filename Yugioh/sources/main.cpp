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

  MainMenu m;
  m.showFullScreen();

  //  Player player1("Nikola");
  //  Player player2("Milan");
    //std::cout << GameSettings::lifePoints;
  //Game game(player1, player2);
  // m.setGame(new Game(player1,player2));
  //game.showFullScreen();



  return app.exec();
}
