#ifndef SPELLTRAPZONE_H
#define SPELLTRAPZONE_H

#include <vector>
#include "Spellcard.h"
#include "Trapcard.h"

class SpellTrapZone {
public:
    SpellTrapZone();
    void placeInSpellTrapZone(Card* card, const int position);
    Card* removeFromSpellTrapZone(Card* card);
    Card* operator[](const int) const;
private:
    std::vector<Card*> m_spellTrapZone;
};

#endif // SPELLTRAPZONE_H
