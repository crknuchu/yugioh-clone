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
    void setMonsterZone(float x, float y);
    void placeInMonsterZone(Card*, Zone*);
    void placeInMonsterZone(Card*, int);
    MonsterCard* removeFromMonsterZone(Zone*);
    void removeFromMonsterZone(int);
    Zone* getZone(Card*);
    float getWidth() const;
    bool isFull() const;
    bool isEmpty() const;
    void colorFreeZones();
    void colorOccupiedZones();
    void colorAvailableZones(MonsterAttribute attribute);
    void refresh();
    float size() const;
    std::vector<Zone*> m_monsterZone;
private:
    float m_width;
};

#endif // MONSTERZONE_H
