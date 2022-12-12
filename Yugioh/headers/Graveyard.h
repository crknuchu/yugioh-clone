#ifndef GRAVEYARD_H
#define GRAVEYARD_H

#include "CardList.h"
#include <optional>

class Graveyard : public CardList {
public:
    Graveyard();
    Graveyard(std::vector<Card*> &initialGraveyard);
    ~Graveyard();
    void sendToGraveyard(Card &card);
    std::vector<Card*> getGraveyard() const;
    Card* removeFromGraveyard(Card &card);
};

#endif // GRAVEYARD_H
