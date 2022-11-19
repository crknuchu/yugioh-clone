#ifndef DECK_H
#define DECK_H

#import <string>
#import "CardList.h"

class Deck : public CardList {
public:
    Deck(const std::string &pathToDeck, std::vector<Card> &deck);
    std::vector<Card> getDeck() const;
    std::vector<Card> draw(int numberOfCards);
    std::vector<Card> shuffleDeck();
};



#endif // DECK_H
