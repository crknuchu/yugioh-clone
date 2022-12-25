#include "headers/Hand.h"
#include <iostream>
#include <algorithm>
#include <optional>

Hand::Hand()
    :m_x(0), m_y(0){};
Hand::Hand(std::vector<Card*> &initialHand)
    :CardList(initialHand){}

std::vector<Card*> Hand::getHand() const{
    return m_cardList;
}

void Hand::setHandCoordinates(float windowWidth, float windowHeight) {
    float cardHeight = 150;
    m_x = windowWidth / 4;
    m_y = windowHeight - cardHeight - 50;
}

void Hand::addToHand(Card &card) {
    float gap = 20;
    card.move(m_x, m_y);
    card.setCardLocation(CardLocation::HAND);
    m_x += card.getWidth() + gap;
    m_cardList.push_back(&card);
}

Card* Hand::removeFromHand(Card &card) {
    auto it = std::find(m_cardList.begin(), m_cardList.end(), &card);
    m_cardList.erase(it);
    return &card;
}

float Hand::size() const {
    return m_cardList.size();
}
