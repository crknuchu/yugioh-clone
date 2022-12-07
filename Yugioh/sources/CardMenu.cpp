#include "headers/CardMenu.h"
#include <iostream>
#include <QGraphicsSceneHoverEvent>
// #include "headers/Card.h"


CardMenu::CardMenu()
{
    // std::cout<<"test";
    setGeometry(0, 0,150,0); //this needs to be the size of the card, not hardcoded and the location just above the card
    setWindowFlags(Qt::FramelessWindowHint);
    layout->addWidget(activateButton);
    layout->addWidget(setButton);
}

CardMenu::CardMenu(int x, int y){
    // setGeometry(0,0parent->getWidth(),0);
    // setGeometry(x,y,100,0);
    setWindowFlags(Qt::FramelessWindowHint);
    // setGeometry(0,0,150,0);
    layout->addWidget(activateButton);
    layout->addWidget(setButton);
    //   show();
}


//void CardMenu::setWidth(int width){
//    this->setWidth(width);
//}

void CardMenu::leaveEvent(QEvent *event){
    hide();
}
