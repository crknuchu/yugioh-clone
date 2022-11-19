#include "headers/Deck.h"
#include <iostream>
#include <chrono>
#include <algorithm>
#include <random>

Deck::Deck(const std::string &pathToDeck, std::vector<Card> &deck)
    :CardList(deck){
    for(auto x : m_cardList){
        std::cout << x.name() << " ";
    }
}

std::vector<Card> Deck::getDeck() const{
    return m_cardList;
}

std::vector<Card> Deck::draw(int numberOfCards) {
    std::vector<Card> cards;
    for(int i = 0; i < numberOfCards; i++){
        cards.push_back(m_cardList.front());
        m_cardList.erase(m_cardList.begin());
    }

    return cards;
}

std::vector<Card> Deck::shuffleDeck()
{
    //generating new random seed every time we call shuffle function
    unsigned seed = std::chrono::system_clock::now()
                        .time_since_epoch()
                        .count();
    std::cout << this->getDeck().front().name();
    shuffle(m_cardList.begin(), m_cardList.end(), std::default_random_engine(seed));
    std::cout << this->getDeck().front().name();
}
