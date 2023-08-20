#include "headers/MonsterZone.h"
#include <algorithm>
#include <iostream>

MonsterZone::MonsterZone()= default;

MonsterZone::~MonsterZone()
{
    for(Zone* zone : m_monsterZone)
    {
        delete zone;
    }

    m_monsterZone.clear();
};

void MonsterZone::setMonsterZone(float x, float y){
    float gap = 40;
    for(int i = 0; i < 5; i++) {
        Zone* zone = new Zone(x, y);
        zone->setBrush(QColor(0,0,200,30));
        m_monsterZone.push_back(zone);
        x += zone->getWidth() + gap;
    }

    m_width = x;
}

auto MonsterZone::removeFromMonsterZone(Zone* targetedZone) -> MonsterCard* {
    auto* card = static_cast<MonsterCard*>(targetedZone->m_pCard);
    targetedZone->m_pCard = nullptr;
    return card;
}

void MonsterZone::removeFromMonsterZone(int zoneNumber) {
    Zone* zone = m_monsterZone[zoneNumber];
    removeFromMonsterZone(zone);
}

auto MonsterZone::getZone(Card *card) -> Zone*
{
    for(Zone* zone : m_monsterZone) {
        if(!zone->isEmpty() && zone->m_pCard == card)
            return zone;
    }

    return nullptr;
}


void MonsterZone::placeInMonsterZone(Card *card, Zone* zone){

    if(!zone->isEmpty()) {
        std::cout << "Spot is occupied" << std::endl;
        return;
    }

    auto* monsterCard = dynamic_cast<MonsterCard*>(card);
    if(monsterCard) {
        zone->putInZone(monsterCard);
        monsterCard->setCardLocation(CardLocation::FIELD);
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
            QColor red50 = Qt::red;
            red50.setAlphaF(0.5);
            zone->setBrush(red50);
            // zone->setBrush(Qt::red);
            zone->update();
        }
    }
}

void MonsterZone::colorOccupiedZones() {
    for(Zone *zone : m_monsterZone) {
        if(!zone->isEmpty()) {
            QColor green50(Qt::green);
            zone->setZValue(-5);
            green50.setAlphaF(0.5);
            zone->setBrush(green50);
            zone->update();
        }
    }
}

void MonsterZone::colorAvailableZones(MonsterAttribute attribute) {
    for(Zone *zone : m_monsterZone) {
        // ovde mora neki uslov tipa if(type == EARTH) ili attribute == nesto ...
        if(!zone->isEmpty() && static_cast<MonsterCard*>(zone->m_pCard)->getAttribute() == attribute) {
            zone->setZValue(100);
            QColor blue50 = Qt::blue;
            blue50.setAlphaF(0.5);
            zone->setBrush(blue50);
            zone->update();
        }
    }
}

void MonsterZone::refresh() {
    for(Zone *zone : m_monsterZone) {
        zone->setBrush(QColor(0,0,200,30));
        zone->setZValue(-10);
        // zone->setBrush(Qt::NoBrush);
        zone->update();
    }
}

auto MonsterZone::isEmpty() const -> bool
{
    for(Zone* zone : m_monsterZone)
    {
        if(!zone->isEmpty())
            return false;
    }
    return true;
}

auto MonsterZone::isFull() const -> bool {
    for(Zone* zone : m_monsterZone) {
        if(zone->isEmpty())
            return false;
    }
    return true;
}

auto MonsterZone::getWidth() const -> float
{
    return m_width;
}

auto MonsterZone::size() const -> float {
    float size = 0;
    for(Zone* zone : m_monsterZone) {
        if(!zone->isEmpty())
            size++;
    }

    return size;
}
