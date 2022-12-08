#include "headers/CardMenu.h"
#include <iostream>
#include <QGraphicsSceneHoverEvent>

CardMenu::CardMenu()
{
    // std::cout<<"test";
    setGeometry(0, 0,150,0); //this needs to be the size of the card, not hardcoded and the location just above the card
    setWindowFlags(Qt::FramelessWindowHint);


    // TODO:
    layout->addWidget(activateButton);
    layout->addWidget(setButton);
}

// Maybe we can pass a Card* here that made this menu
CardMenu::CardMenu(int x, int y){
    // setGeometry(0,0parent->getWidth(),0);
    // setGeometry(x,y,100,0);
    setWindowFlags(Qt::FramelessWindowHint);
    // setGeometry(0,0,150,0);
    layout->addWidget(activateButton);
    layout->addWidget(setButton);
    layout->addWidget(summonButton);
    //   show();
}


//void CardMenu::setWidth(int width){
//    this->setWidth(width);
//}

void CardMenu::leaveEvent(QEvent *event){
    hide();
}
