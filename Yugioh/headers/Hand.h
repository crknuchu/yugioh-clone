#ifndef HAND_H
#define HAND_H

#include "CardList.h"
#include <optional>

class Hand : public CardList {
public:
    Hand();
    Hand(std::vector<Card*> &initialHand);
    std::vector<Card*> getHand() const;
    void setHandCoordinates(float, float);
    void addToHand(Card &card);
    Card* removeFromHand(Card &card);
private:
    float m_x;
    float m_y;
};

#endif // HAND_H
