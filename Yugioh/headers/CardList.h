#ifdef CARDLIST_H
#define CARDLIST_H

#include <vector>
#include "Card.h"

class CardList {
public:
    CardList();
    ~CardList();
protected:
    vector<Card> m_cardList;
}

#endif
