#include "headers/MonsterZone.h"
#include <algorithm>
#include <iostream>

MonsterZone::MonsterZone(){
    std::cout  << "udjem li ovde" << std::endl;
}

MonsterZone::~MonsterZone()
{
    for(Zone* zone : m_monsterZone)
    {
        delete zone;
    }

    m_monsterZone.clear();
};

void MonsterZone::setMonsterZone(float x, float y){
    float gap = 20;
    for(int i = 0; i < 5; i++) {
        Zone* zone = new Zone(x, y);
        zone->setBrush(QColor(0,0,200,30));
        m_monsterZone.push_back(zone);
        x += zone->getWidth() + gap;
    }

    m_width = x;
}

MonsterCard* MonsterZone::removeFromMonsterZone(Zone* targetedZone) {
    MonsterCard* card = static_cast<MonsterCard*>(targetedZone->m_pCard);
    targetedZone->m_pCard = nullptr;
    return card;
}

void MonsterZone::removeFromMonsterZone(int zoneNumber) {
    Zone* zone = m_monsterZone[zoneNumber];
    removeFromMonsterZone(zone);
}


void MonsterZone::placeInMonsterZone(Card *card, Zone* zone){

    if(!zone->isEmpty()) {
        std::cout << "Spot is occupied" << std::endl;
        return;
    }

    MonsterCard* monsterCard = dynamic_cast<MonsterCard*>(card);
    if(monsterCard) {
        zone->putInZone(monsterCard);
    }
    else {
        std::cout << "Only monster cards can be put in monster zone" << std::endl;
        return;
    }
}

void MonsterZone::placeInMonsterZone(Card *card, int zoneNumber)
{
    if(zoneNumber < 1 || zoneNumber > 5) {
        std::cout << "Invalid zone number" << std::endl;
        return;
    }

    Zone* zone = m_monsterZone[zoneNumber - 1];
    placeInMonsterZone(card, zone);
}



void MonsterZone::colorFreeZones() {
    for(Zone *zone : m_monsterZone) {
        if(zone->isEmpty()) {
            zone->setBrush(Qt::red);
            zone->update();
        }
    }
}

void MonsterZone::colorOccupiedZones() {
    for(Zone *zone : m_monsterZone) {
        if(!zone->isEmpty()) {
            zone->setBrush(Qt::green);
            zone->update();
        }
    }
}

void MonsterZone::refresh() {
    for(Zone *zone : m_monsterZone) {
        zone->setBrush(QColor(0,0,200,30));
        zone->update();
    }
}

bool MonsterZone::isFull() const {
    for(Zone* zone : m_monsterZone) {
        if(zone->isEmpty())
            return false;
    }
    return true;
}

float MonsterZone::getWidth() const
{
    return m_width;
}

float MonsterZone::size() const {
    float size = 0;
    for(Zone* zone : m_monsterZone) {
        if(!zone->isEmpty())
            size++;
    }

    return size;
}
