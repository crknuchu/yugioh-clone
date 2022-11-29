#ifndef MONSTERZONE_H
#define MONSTERZONE_H

#include <vector>
#include "Monstercard.h"

class MonsterZone {
public:
    MonsterZone();
private:
    std::vector<MonsterCard*> m_monsterZone;
};

#endif // MONSTERZONE_H
