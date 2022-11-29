#include "headers/MonsterZone.h"
#include <algorithm>
#include <iostream>

MonsterZone::MonsterZone()
    :m_monsterZone({nullptr, nullptr, nullptr, nullptr, nullptr}){};

MonsterCard* MonsterZone::removeFromMonsterZone(MonsterCard *card) {
    auto it = std::find(m_monsterZone.begin(), m_monsterZone.end(), card);
    m_monsterZone.erase(it);
    return card;
}

void MonsterZone::placeInMonsterZone(Card *card, const int position){
    if(position < 1 || position > 5) {
        std::cout << "Incorrect field spot" << std::endl;
        return;
    }

    //-1 is there because position can be 1 to 5 translated to arrays language its 0 to 4
    if(m_monsterZone[position - 1] != nullptr) {
        std::cout << "Spot is occupied" << std::endl;
        return;
    }

    MonsterCard* monsterCard = dynamic_cast<MonsterCard*>(card);
    if(monsterCard) {
        m_monsterZone.insert(m_monsterZone.begin() + position - 1, monsterCard);
    }
    else {
        std::cout << "Only monster cards can be put in monster zone" << std::endl;
        return;
    }
}

MonsterCard* MonsterZone::operator[](const int i) const {
    return m_monsterZone[i];
}

