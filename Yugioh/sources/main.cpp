#include <iostream>
#include "headers/Game.h"
#include <QApplication>

int main(int argc,char **argv)
{
    QApplication app(argc,argv);
    Game *game = new Game();
    game->show();

    app.exec();
    return 0;
}
