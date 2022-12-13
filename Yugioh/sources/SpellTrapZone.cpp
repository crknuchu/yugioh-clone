#include "headers/SpellTrapZone.h"
#include <iostream>

SpellTrapZone::SpellTrapZone(){
    float x = 0;
    float y = 470;
    float gap = 20;
    for(int i = 0; i < 5; i++) {
        Zone* zone = new Zone(x, y);
        m_spellTrapZone.push_back(zone);
        x += zone->getWidth() + gap;
    }
}

SpellTrapZone::~SpellTrapZone()
{
    for(Zone* zone : m_spellTrapZone){
        delete zone;
    }

    m_spellTrapZone.clear();
};

Card* SpellTrapZone::removeFromSpellTrapZone(Zone* targetedZone) {
    Card* card = targetedZone->m_pCard;
    targetedZone->m_pCard = nullptr;
    return card;
}

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

void SpellTrapZone::colorFreeZones() {
    for(Zone *zone : m_spellTrapZone) {
        if(zone->isEmpty()) {
            zone->setBrush(Qt::red);
            zone->update();
        }
    }
}

void SpellTrapZone::colorOccupiedZones() {
    for(Zone *zone : m_spellTrapZone) {
        if(!zone->isEmpty()) {
            zone->setBrush(Qt::green);
            zone->update();
        }
    }
}

void SpellTrapZone::refresh() {
    for(Zone *zone : m_spellTrapZone) {
        zone->setBrush(Qt::NoBrush);
        zone->update();
    }
}

bool SpellTrapZone::isFull() const {
    for(Zone* zone : m_spellTrapZone) {
        if(zone->isEmpty())
            return false;
    }
    return true;
}

