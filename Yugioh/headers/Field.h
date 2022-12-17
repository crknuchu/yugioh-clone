#ifndef FIELD_H
#define FIELD_H
#include "MonsterZone.h"
#include "SpellTrapZone.h"
#include "Graveyard.h"
#include "Deck.h"

class Field {
public:
    Field();

    MonsterZone monsterZone;
    SpellTrapZone spellTrapZone;
    Graveyard graveyard;
    Deck deck;
};

#endif // FIELD_H
