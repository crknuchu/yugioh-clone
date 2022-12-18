#ifndef DECK_H
#define DECK_H

#include <string>
#include "CardList.h"
#include "Monstercard.h"

class Deck : public CardList {
public:
    Deck();
    Deck(const std::string &pathToDeck, std::vector<Card*> &deck);
    void setDeck(float, float, int);
    std::vector<Card*> getDeck() const;
    Card* draw();
    std::vector<Card*> draw(int numberOfCards);
    void shuffleDeck();

    std::vector<Card *> uiDeck;
};



#endif // DECK_H
