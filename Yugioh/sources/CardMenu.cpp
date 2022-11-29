#include "headers/CardMenu.h"
#include <iostream>

CardMenu::CardMenu()
{
    // std::cout<<"test";
    setGeometry(0,0,150,0); //this needs to be the size of the card, not hardcoded and the location just above the card
    layout->addWidget(activateButton);
    layout->addWidget(setButton);
    show();
}

// CardMenu::CardMenu(auto *parent){
//     //   setGeometry(0,0,parent->getWidth(),0);
//     //   setWindowFlags(Qt::FramelessWindowHint);
//     setGeometry(0,0,150,0);
//     layout->addWidget(activateButton);
//     layout->addWidget(setButton);
//     //   show();
// }