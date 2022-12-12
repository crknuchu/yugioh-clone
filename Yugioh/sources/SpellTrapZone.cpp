#include "headers/SpellTrapZone.h"
#include <iostream>

SpellTrapZone::SpellTrapZone(){
    float x = 0;
    float y = 470;
    float gap = 20;
    for(int i = 0; i < 5; i++) {
        Zone* z = new Zone(x, y);
        m_spellTrapZone.push_back(z);
        x += z->getWidth() + gap;
    }
}

SpellTrapZone::~SpellTrapZone()
{
    for(Zone* zone : m_spellTrapZone){
        delete zone;
    }

    m_spellTrapZone.clear();
};

//Card* SpellTrapZone::removeFromSpellTrapZone(Card *card) {
//    auto it = std::find(m_spellTrapZone.begin(), m_spellTrapZone.end(), card);
//    m_spellTrapZone.erase(it);
//    return card;
//}

void SpellTrapZone::placeInSpellTrapZone(Card *card, Zone* zone){

    if(!zone->isEmpty()) {
        std::cout << "Spot is occupied" << std::endl;
        return;
    }

    SpellCard* spellCard = dynamic_cast<SpellCard*>(card);
    TrapCard* trapCard = dynamic_cast<TrapCard*>(card);
    if(spellCard) {
        zone->putInZone(spellCard);
    }
    else if(trapCard) {
        zone->putInZone(trapCard);
    }
    else {
        std::cout << "Only spell or trap cards can be put in spell/trap zone" << std::endl;
        return;
    }
}
