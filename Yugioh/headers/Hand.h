#ifndef HAND_H
#define HAND_H

#include "CardList.h"
#include <optional>

class Hand : public CardList {
public:
    Hand(std::vector<Card> &initialHand);
    std::vector<Card> getHand() const;
    void addToHand(Card &card);
    std::optional<Card> removeFromHand(Card &card);
};

#endif // HAND_H
