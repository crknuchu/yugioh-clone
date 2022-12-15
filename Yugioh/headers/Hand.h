#ifndef HAND_H
#define HAND_H

#include "CardList.h"
#include <optional>

class Hand : public CardList {
public:
    Hand();
    Hand(std::vector<Card*> &initialHand);
    std::vector<Card*> getHand() const;
    void addToHand(Card &card);
    Card* removeFromHand(Card &card);
private:
    float m_width;
};

#endif // HAND_H
