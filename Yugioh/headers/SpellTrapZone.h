#ifndef SPELLTRAPZONE_H
#define SPELLTRAPZONE_H

#include <vector>
#include "Spellcard.h"
#include "Trapcard.h"

class SpellTrapZone {
public:
    SpellTrapZone();
private:
    std::vector<Card*> m_spellTrapzone;
};

#endif // SPELLTRAPZONE_H
