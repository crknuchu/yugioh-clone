#ifndef GRAVEYARD_H
#define GRAVEYARD_H

#include "CardList.h"
#include <optional>

class Graveyard : public CardList {
public:
    Graveyard(std::vector<Card> &initialGraveyard);
    void sendToGraveyard(const Card &card);
    std::vector<Card> getGraveyard() const;
    std::optional<Card>  removeFromGraveyard(const Card &card);
};

#endif // GRAVEYARD_H
