#ifndef MONSTERZONE_H
#define MONSTERZONE_H

#include <vector>
#include "Monstercard.h"

// Placeholder forward declaration, to be removed in the future
class Zone;

class MonsterZone : public QVector<Zone *>  {
public:
    MonsterZone();
    void placeInMonsterZone(Card* card, const int position);
    MonsterCard* removeFromMonsterZone(MonsterCard* card);
    MonsterCard* operator[](const int) const;
private:
    std::vector<MonsterCard*> m_monsterZone;
};

#endif // MONSTERZONE_H
