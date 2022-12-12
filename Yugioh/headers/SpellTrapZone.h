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
    void placeInSpellTrapZone(Card*, Zone*);
    Card* removeFromSpellTrapZone(Zone*);
    bool isFull() const;
    void colorFreeZones();
    void colorOccupiedZones();
    void refresh();

    std::vector<Zone*> m_spellTrapZone;
};

#endif // SPELLTRAPZONE_H
