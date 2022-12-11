#ifndef MONSTERZONE_H
#define MONSTERZONE_H

#include <vector>
#include "Monstercard.h"
#include "Zone.h"
#include <QVector>

class MonsterZone : public QVector<Zone*> {
public:
    MonsterZone();
    void placeInMonsterZone(Card* card, int position);
//    MonsterCard* removeFromMonsterZone(MonsterCard* card);
//    MonsterCard* operator[](const int) const;
    bool isFull() const;
    void colorFreeZones();
    std::vector<Zone*> m_monsterZone;
};

#endif // MONSTERZONE_H
