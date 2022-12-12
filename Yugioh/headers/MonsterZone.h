#ifndef MONSTERZONE_H
#define MONSTERZONE_H

#include <vector>
#include "Monstercard.h"
#include "Zone.h"
#include <QVector>

class MonsterZone : public QVector<Zone*> {
public:
    MonsterZone();
    ~MonsterZone();
    void placeInMonsterZone(Card*, Zone*);
    MonsterCard* removeFromMonsterZone(Zone*);
    bool isFull() const;
    void colorFreeZones();
    void colorOccupiedZones();
    void refresh();

    std::vector<Zone*> m_monsterZone;
};

#endif // MONSTERZONE_H
