#ifndef DECK_H
#define DECK_H

#import <string>
#import <vector>
#import "Card.h"

class Deck {
public:
    Deck(const std::string &pathToDeck, std::vector<Card> &deck);
};


#endif // DECK_H
