#include "headers/Deck.h"
#include "headers/Monstercard.h"
#include <iostream>
#include <chrono>
#include <algorithm>
#include <random>

Deck::Deck()= default;
Deck::Deck(std::vector<Card*> &deck)
    :CardList(deck){}

auto Deck::getDeck() const -> std::vector<Card*>{
    return m_cardList;
}

void Deck::setDeck(float x, float y, int playerNumber) {
    float gap = 2;
    for(int i = 0; i < 5; i++) { //for now its hardcoded but needs to be deck.size / 4
        auto* placeholderCard = new MonsterCard("placeholder", 0,0,1,MonsterType::AQUA,
                                          MonsterKind::NORMAL_MONSTER, MonsterAttribute::DARK,
                                          false, MonsterPosition::FACE_UP_DEFENSE, true, CardType::MONSTER_CARD,
                                          CardLocation::DECK, "placeholder",":/resources/pictures/card_back.jpg", false);


        placeholderCard->setPos(x,y);
        uiDeck.push_back(placeholderCard);
        playerNumber == 1 ? x += gap : x-=gap;
    }
}

auto Deck::draw() -> Card*{
    Card* drawnCard = m_cardList.front();
    m_cardList.erase(m_cardList.begin());
    return drawnCard;
};

auto Deck::draw(int numberOfCards) -> std::vector<Card*> {
    std::vector<Card*> cards;
    for(int i = 0; i < numberOfCards; i++){
        cards.push_back(m_cardList.front());
        m_cardList.erase(m_cardList.begin());
    }

    return cards;
}

void Deck::shuffleDeck(unsigned seed)
{
    shuffle(m_cardList.begin(), m_cardList.end(), std::default_random_engine(seed));
}
