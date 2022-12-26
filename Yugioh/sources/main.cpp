#include "headers/Player.h"
#include "headers/Game.h"
#include "headers/mainmenu.h"
#include <iostream>

#include <QApplication>

int main(int argc,char **argv)
{
    QApplication app(argc, argv);

    MainMenu mainMenu;

    mainMenu.show();

    return app.exec();
}
