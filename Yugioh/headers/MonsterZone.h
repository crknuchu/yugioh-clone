#ifndef MONSTERZONE_H
#define MONSTERZONE_H

#include <vector>
#include "Monstercard.h"

class MonsterZone {
public:
    MonsterZone();
    void placeInMonsterZone(Card* card, const int position);
    MonsterCard* removeFromMonsterZone(MonsterCard* card);
    MonsterCard* operator[](const int) const;
    std::vector<MonsterCard*>getMonsterZone();
private:
    std::vector<MonsterCard*> m_monsterZone;
};

#endif // MONSTERZONE_H
