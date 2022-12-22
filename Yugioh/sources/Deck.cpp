#include "headers/Deck.h"
#include <iostream>
#include <chrono>
#include <algorithm>
#include <random>

Deck::Deck(){}

Deck::Deck(const std::string &pathToDeck, std::vector<Card*> &deck)
    :CardList(deck){
    for(auto card : m_cardList){
        std::cout << card->getCardName() << " ";
    }
}

std::vector<Card*> Deck::getDeck() const{
    return m_cardList;
}

void Deck::setDeck(float x, float y, int playerNumber) {
    float gap = 2;
    for(int i = 0; i < 5; i++) { //for now its hardcoded but needs to be deck.size / 4
        MonsterCard* placeholderCard = new MonsterCard("placeholder", 0,0,1,MonsterType::AQUA,
                                          MonsterKind::NORMAL_MONSTER, MonsterAttribute::DARK,
                                          false, Position::DEFENSE, true, CardType::MONSTER_CARD,
                                          CardLocation::DECK, "placeholder",":/resources/pictures/card_back.jpg", false);

        placeholderCard->setPos(x,y);
        uiDeck.push_back(placeholderCard);
        playerNumber == 1 ? x += gap : x-=gap;
    }
}

Card* Deck::draw(){
    Card* drawnCard = m_cardList.front();
    m_cardList.erase(m_cardList.begin());
    return drawnCard;
};

std::vector<Card*> Deck::draw(int numberOfCards) {
    std::vector<Card*> cards;
    for(int i = 0; i < numberOfCards; i++){
        cards.push_back(m_cardList.front());
        m_cardList.erase(m_cardList.begin());
    }

    return cards;
}

void Deck::shuffleDeck()
{
    //generating new random seed every time we call shuffle function
    unsigned seed = std::chrono::system_clock::now()
                        .time_since_epoch()
                        .count();

    shuffle(m_cardList.begin(), m_cardList.end(), std::default_random_engine(seed));
}
