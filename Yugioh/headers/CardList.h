#ifndef CARDLIST_H
#define CARDLIST_H

#include <vector>
#include <QVector>
#include "Card.h"

class CardList : public QVector<Card*>
{
public:
    virtual ~CardList() = default;
protected:
    CardList();
    CardList(std::vector<Card*> &cardList);
    std::vector<Card*> m_cardList;
};

#endif
