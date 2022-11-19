#ifndef CARDLIST_H
#define CARDLIST_H

#include <vector>
#include "Card.h"

class CardList {
public:
    virtual ~CardList() = default;
protected:
    CardList(std::vector<Card*> &cardList);
    std::vector<Card*> m_cardList;
};

#endif
