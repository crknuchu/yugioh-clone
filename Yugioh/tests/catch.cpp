#define CATCH_CONFIG_RUNNER
#include "catch.hpp"


#include "headers/mainmenu.h"
#include <iostream>
#include <QApplication>

int main(int argc,char **argv)
{
    QApplication app(argc, argv);

    // MainMenu mainMenu;

    // mainMenu.show();

    return Catch::Session().run(argc,argv);
}
