#include "headers/mainmenu.h"
#include <iostream>

#include <QApplication>

#include "headers/Game.h"
#include "headers/Player.h"

int main(int argc,char **argv)
{
    QApplication app(argc, argv);

//    MainMenu mainMenu;

//    mainMenu.show();

    Player *player1 = new Player("Nikola");
    Player *player2 = new Player("Milan");
    Game *game = new Game(*player1, *player2);

    game->show();


    return app.exec();
}
