#ifndef DECK_H
#define DECK_H

#include <string>
#include "CardList.h"

class Deck : public CardList {
public:
    Deck(const std::string &pathToDeck, std::vector<Card> &deck);
    std::vector<Card> getDeck() const;
    std::vector<Card> draw(int numberOfCards);
    void shuffleDeck();
};



#endif // DECK_H
