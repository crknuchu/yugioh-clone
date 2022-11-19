#include "headers/Graveyard.h"
#include <iostream>
#include <algorithm>
#include <optional>

Graveyard::Graveyard(std::vector<Card> &initialGraveyard)
    :CardList(initialGraveyard)
{
    for(auto x : m_cardList) {
        std::cout << x.name() << " ";
    }
}

void Graveyard::sendToGraveyard(const Card &card) {
    m_cardList.push_back(card);
}

std::vector<Card> Graveyard::getGraveyard() const{
    return m_cardList;
}

std::optional<Card> Graveyard::removeFromGraveyard(const Card &card)
{
   std::vector<Card>::iterator it = std::find(m_cardList.begin(), m_cardList.end(), card);
   if(it == m_cardList.end())
       return {};
    std::cout << m_cardList.front().name();
    m_cardList.erase(it);
    std::cout << m_cardList.front().name();
    return card;
}


