#include "headers/CardMenu.h"
#include <iostream>

CardMenu::CardMenu()
{
    // std::cout<<"test";
    show();
}

CardMenu::CardMenu(Card *parent){
      setGeometry(0,0,parent->getWidth(),0);
      setWindowFlags(Qt::FramelessWindowHint);
      layout->addWidget(activateButton);
      layout->addWidget(setButton);
    //   show();
}