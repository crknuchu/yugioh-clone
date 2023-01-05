#include "headers/mainmenu.h"
#include <iostream>

#include <QApplication>
#include"headers/mainmenu.h"
#include <iostream>
#include <QApplication>

int main(int argc,char **argv)
{
    QApplication app(argc, argv);

    MainMenu m;

    //MainMenu m;
    m.showFullScreen();


    return app.exec();
}
