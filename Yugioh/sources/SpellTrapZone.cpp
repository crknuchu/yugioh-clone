#include "headers/SpellTrapZone.h"
#include <iostream>

SpellTrapZone::SpellTrapZone(){}

SpellTrapZone::~SpellTrapZone()
{
    for(Zone* zone : m_spellTrapZone){
        delete zone;
    }

    m_spellTrapZone.clear();
};

void SpellTrapZone::setSpellTrapZone(float x , float y){
    float gap = 20;
    for(int i = 0; i < 5; i++) {
        Zone* zone = new Zone(x, y);
        zone->setBrush(QColor(0,200,0,30));
        m_spellTrapZone.push_back(zone);
        x += zone->getWidth() + gap;
    }

    m_width = x;
}

Card* SpellTrapZone::removeFromSpellTrapZone(Zone* targetedZone) {
    Card* card = targetedZone->m_pCard;
    targetedZone->m_pCard = nullptr;
    return card;
}

void SpellTrapZone::removeFromSpellTrapZone(int zoneNumber) {
    Zone* zone = m_spellTrapZone[zoneNumber];
    removeFromSpellTrapZone(zone);
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

void SpellTrapZone::placeInSpellTrapZone(Card *card, int zoneNumber)
{
    if(zoneNumber < 1 || zoneNumber > 5) {
        std::cout << "Invalid zone number" << std::endl;
        return;
    }

    Zone* zone = m_spellTrapZone[zoneNumber - 1];
    placeInSpellTrapZone(card, zone);
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

float SpellTrapZone::getWidth() const
{
    return m_width;
}
