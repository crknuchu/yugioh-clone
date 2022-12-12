#include "headers/CardMenu.h"

CardMenu::CardMenu()
{
    setWindowFlags(Qt::FramelessWindowHint);
    hide(); // the menu is not visible at default
}

void CardMenu::update(QMap<QString,bool> flags)
{
    if(flags["activate"] == true){
        layout->addWidget(activateButton);
    }
    else{
        layout->removeWidget(activateButton);
    }
    if(flags["set"] == true){
        layout->addWidget(setButton);
    }
    else{
        layout->removeWidget(setButton);
    }
    if(flags["summon"] == true){
        layout->addWidget(summonButton);        
    }
    else{
        layout->removeWidget(summonButton);
    }
    if(flags["reposition"] == true){
        layout->addWidget(repositionButton);
    }
    else{
        layout->removeWidget(repositionButton);
    }
    if(flags["attack"] == true){
        layout->addWidget(attackButton);        
    }
    else{
        layout->removeWidget(attackButton);
    }    
}