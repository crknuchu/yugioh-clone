#include "headers/CardMenu.h"

CardMenu::CardMenu(QMap<QString,bool> flags)
{
    setWindowFlags(Qt::FramelessWindowHint);

    if(flags["activate"] == true){
        layout->addWidget(activateButton);
    }
    if(flags["set"] == true){
        layout->addWidget(setButton);
    }
    if(flags["summon"] == true){
        layout->addWidget(summonButton);        
    }
    if(flags["reposition"] == true){
        layout->addWidget(repositionButton);
    }
    if(flags["attack"] == true){
        layout->addWidget(attackButton);        
    }
    
    hide(); // the menu is not visible at default
}