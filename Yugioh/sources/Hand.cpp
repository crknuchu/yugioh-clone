#include "headers/Hand.h"
#include <iostream>
#include <algorithm>
#include <optional>

Hand::Hand()
    :m_x(0), m_y(0){};
Hand::Hand(std::vector<Card*> &initialHand)
    :CardList(initialHand){}

std::vector<Card*> Hand::getHand() const{
    return this->m_cardList;
}

void Hand::setHandCoordinates(float windowWidth, float windowHeight, int playerNumber) {
    float cardHeight = 150;
    if(playerNumber == 1) {
        m_x = windowWidth / 4;
        m_y = windowHeight - cardHeight - 50;
    }
    else if(playerNumber == 2){
        m_x = windowWidth / 4;
        m_y = 0;
    }
}

void Hand::addToHand(Card &card) {
    float gap = 20;
    card.move(m_x, m_y);
    card.setCardLocation(CardLocation::HAND);
    m_x += card.getWidth() + gap;
    m_cardList.push_back(&card);
}

Card* Hand::removeFromHand(Card &cardToBeRemoved) {
    std::cout << "Card to be removed: " << cardToBeRemoved << std::endl;
    float gap = 20;
    bool found = false;
    std::vector<Card*> cardsToBeFixed;
    for(Card* card : m_cardList) {
        std::cout << "Card in loop: " << *card << std::endl;
        if(found) {
            cardsToBeFixed.push_back(card);
        }

        if(card->getCardName() == cardToBeRemoved.getCardName())
            found = true;
    }
    auto it = std::find(m_cardList.begin(), m_cardList.end(), &cardToBeRemoved);
    m_x -= (cardToBeRemoved.getWidth() + gap);
    m_cardList.erase(it);

    fixCardsPosition(cardsToBeFixed);
    return &cardToBeRemoved;
}

void Hand::fixCardsPosition(std::vector<Card *> &cardsToBeFixed) {
    float gap = 20;
    for(Card* card : cardsToBeFixed) {
        auto it = std::find(m_cardList.begin(), m_cardList.end(), card);
        m_cardList.erase(it);
        m_x -= (card->getWidth() + gap);
    }

    for(Card* card : cardsToBeFixed)
        addToHand(*card);
}

float Hand::size() const {
    return this->m_cardList.size();
}
