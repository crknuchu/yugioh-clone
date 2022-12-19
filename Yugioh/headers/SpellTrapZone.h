#ifndef SPELLTRAPZONE_H
#define SPELLTRAPZONE_H

#include <vector>
#include <QVector>
#include "Spellcard.h"
#include "Trapcard.h"
#include "Zone.h"

class SpellTrapZone : public QVector<Zone*> {
public:
    SpellTrapZone();
    ~SpellTrapZone();
    void setSpellTrapZone(float x, float y);
    void placeInSpellTrapZone(Card*, Zone*);
    Card* removeFromSpellTrapZone(Zone*);
    bool isFull() const;
    void colorFreeZones();
    void colorOccupiedZones();
    void refresh();
    float getWidth() const;

    std::vector<Zone*> m_spellTrapZone;

private:
    float m_width;
};

#endif // SPELLTRAPZONE_H
