#include "headers/MonsterZone.h"
#include <algorithm>
#include <iostream>

MonsterZone::MonsterZone(){
    float x = 0;
    float y = 300;
    float gap = 20;
    for(int i = 0; i < 5; i++) {
        Zone* z = new Zone(x, y);
        m_monsterZone.push_back(z);
        x += z->getWidth() + gap;
    }
}

MonsterZone::~MonsterZone()
{
    for(Zone* zone : m_monsterZone) {
        delete zone;
    }

    m_monsterZone.clear();
};

//MonsterCard* MonsterZone::removeFromMonsterZone(MonsterCard *card) {
//    auto it = std::find(m_monsterZone.begin(), m_monsterZone.end(), card);
//    m_monsterZone.erase(it);
//    return card;
//}

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

void MonsterZone::colorFreeZones() {
    for(Zone *zone : m_monsterZone) {
        if(zone->isEmpty()) {
            zone->setBrush(Qt::red);
            zone->update();
        }
    }
}

void MonsterZone::refresh() {
    for(Zone *zone : m_monsterZone) {
        zone->setBrush(Qt::NoBrush);
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

//MonsterCard* MonsterZone::operator[](const int i) const {
//    return m_monsterZone[i];
//}

