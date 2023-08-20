#include "headers/mainmenu.h"
#include <iostream>

#include <QApplication>
#include"headers/mainmenu.h"
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
