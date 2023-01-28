#define CATCH_CONFIG_RUNNER
#include "headers/mainmenu.h"
#include <iostream>

#include <QApplication>
#include <iostream>
#include <QApplication>

auto main(int argc,char **argv) -> int
{
    QApplication app(argc, argv);

    MainMenu m;

    //MainMenu m;
    m.showFullScreen();


    return app.exec();
}
