#include "headers/SpellTrapZone.h"
#include <iostream>

SpellTrapZone::SpellTrapZone()
    :m_spellTrapZone({nullptr,nullptr,nullptr,nullptr,nullptr}){};

Card* SpellTrapZone::removeFromSpellTrapZone(Card *card) {
    auto it = std::find(m_spellTrapZone.begin(), m_spellTrapZone.end(), card);
    m_spellTrapZone.erase(it);
    return card;
}

void SpellTrapZone::placeInSpellTrapZone(Card *card, const int position){
    if(position < 1 || position > 5) {
        std::cout << "Incorrect field spot" << std::endl;
        return;
    }

    //-1 is there because position can be 1 to 5 translated to arrays language its 0 to 4
    if(m_spellTrapZone[position - 1] != nullptr) {
        std::cout << "Spot is occupied" << std::endl;
        return;
    }

    SpellCard* spellCard = dynamic_cast<SpellCard*>(card);
    TrapCard* trapCard = dynamic_cast<TrapCard*>(card);
    if(spellCard) {
        m_spellTrapZone.insert(m_spellTrapZone.begin() + position - 1, spellCard);
    }
    else if(trapCard) {
        m_spellTrapZone.insert(m_spellTrapZone.begin() + position - 1, trapCard);
    }
    else {
        std::cout << "Only spell or trap cards can be put in spell/trap zone" << std::endl;
        return;
    }
}

Card* SpellTrapZone::operator[](const int i) const {
    return m_spellTrapZone[i];
}
