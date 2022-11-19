#include "headers/Hand.h"
#include <iostream>
#include <algorithm>
#include <optional>

Hand::Hand(std::vector<Card> &initialHand)
    :CardList(initialHand){
    for(auto x : m_cardList){
        std::cout << x.name() << " " ;
    }
}

std::vector<Card> Hand::getHand() const{
    return m_cardList;
}

void Hand::addToHand(Card &card) {
    m_cardList.push_back(card);
}

std::optional<Card> Hand::removeFromHand(Card &card) {
    std::vector<Card>::iterator it = std::find(m_cardList.begin(), m_cardList.end(), card);
    if(it == m_cardList.end())
        return {};

     m_cardList.erase(it);
     return card;
}
