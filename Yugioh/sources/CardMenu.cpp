#include "headers/CardMenu.h"

CardMenu::CardMenu()
{
    setWindowFlags(Qt::FramelessWindowHint);
    setUpLayout();
    hide();
}

void CardMenu::setUpLayout()
{
    layout->addWidget(activateButton);
    layout->addWidget(setButton);
    layout->addWidget(summonButton);        
    layout->addWidget(repositionButton);   
    layout->addWidget(attackButton); 
    layout->addWidget(attackDirectlyButton);       
}

void CardMenu::update(QMap<QString,bool> flags)
{
    if(flags["activate"] == true){
        activateButton->show();
    }
    else{
        activateButton->hide();
    }
    if(flags["set"] == true){
        setButton->show();
    }
    else{
        setButton->hide();
    }
    if(flags["summon"] == true){
        summonButton->show();       
    }
    else{
        summonButton->hide();
    }
    if(flags["reposition"] == true){
        repositionButton->show();
    }
    else{
        repositionButton->hide();
    }
    if(flags["attack"] == true){
        attackButton->show();    
    }
    else{
        attackButton->hide();
    }    
    //attackDirectly to be implemented later
    // if(flags["attackDirectly"] == true){
    //     attackDirectlyButton->show();
    // }
    // else{
    //     attackDirectlyButton->hide();
    // }
}
