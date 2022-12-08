#include "headers/CardMenu.h"
#include <iostream>
#include <QGraphicsSceneHoverEvent>

CardMenu::CardMenu() //need arguments for menu options
{
    setWindowFlags(Qt::FramelessWindowHint);

    bool tmpArgument = true;

    if(tmpArgument == true){
        layout->addWidget(activateButton);
    }
    if(tmpArgument == true){
        layout->addWidget(setButton);
    }
    if(tmpArgument == true){
        layout->addWidget(summonButton);        
    }
    if(tmpArgument == true){
        layout->addWidget(repositionButton);
    }
    if(tmpArgument == true){
        layout->addWidget(attackButton);        
    }
    
    hide();
}