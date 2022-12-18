#include "headers/Hand.h"
#include <iostream>
#include <algorithm>
#include <optional>

Hand::Hand()
    :m_width(200){};
Hand::Hand(std::vector<Card*> &initialHand)
    :CardList(initialHand), m_width(200){}

std::vector<Card*> Hand::getHand() const{
    return m_cardList;
}

void Hand::addToHand(Card &card) {
    float gap = 2;
    float y = 700;
    card.move(m_width, y);
    card.setCardLocation(CardLocation::HAND);
    m_width += card.getWidth() + gap;
    m_cardList.push_back(&card);
}

Card* Hand::removeFromHand(Card &card) {
    auto it = std::find(m_cardList.begin(), m_cardList.end(), &card);
    m_cardList.erase(it);
    return &card;
}
