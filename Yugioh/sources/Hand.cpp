#include "headers/Hand.h"
#include <iostream>
#include <algorithm>
#include <optional>

Hand::Hand(){};
Hand::Hand(std::vector<Card*> &initialHand)
    :CardList(initialHand){
    for(auto card : m_cardList){
        std::cout << card->getCardName() << " " ;
    }
}

std::vector<Card*> Hand::getHand() const{
    return m_cardList;
}

void Hand::addToHand(Card &card) {
    m_cardList.push_back(&card);
}

Card* Hand::removeFromHand(Card &card) {
    auto it = std::find(m_cardList.begin(), m_cardList.end(), &card);
    m_cardList.erase(it);
    return &card;
}
