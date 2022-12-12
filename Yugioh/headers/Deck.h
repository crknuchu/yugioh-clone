#ifndef DECK_H
#define DECK_H

#include <string>
#include "CardList.h"
#include <QVector>

class Deck : public CardList {
public:
    Deck();
    Deck(const std::string &pathToDeck, std::vector<Card*> &deck);
    ~Deck();
    std::vector<Card*> getDeck() const;
    Card* draw();
    std::vector<Card*> draw(int numberOfCards);
    void shuffleDeck();
};



#endif // DECK_H
