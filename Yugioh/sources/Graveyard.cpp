#include "headers/Graveyard.h"
#include <iostream>
#include <algorithm>
#include <optional>

Graveyard::Graveyard(){}
Graveyard::Graveyard(std::vector<Card*> &initialGraveyard)
    :CardList(initialGraveyard)
{
    for(auto x : m_cardList) {
        std::cout << x->getCardName() << " ";
    }
}
Graveyard::~Graveyard(){}

void Graveyard::sendToGraveyard(Card &card) {
    m_cardList.push_back(&card);
}

std::vector<Card*> Graveyard::getGraveyard() const{
    return m_cardList;
}

Card* Graveyard::removeFromGraveyard(Card &card)
{
    auto it = std::find(m_cardList.begin(), m_cardList.end(), &card);
    m_cardList.erase(it);
    return &card;
}


