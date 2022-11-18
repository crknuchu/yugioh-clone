#ifndef CARDLIST_H
#define CARDLIST_H

#include <vector>
#include "Card.h"

class CardList {
public:
    virtual ~CardList() = default;
protected:
    CardList(vector<Card> &cardList);
    vector<Card *> m_cardList;
};

#endif
