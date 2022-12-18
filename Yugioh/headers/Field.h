#ifndef FIELD_H
#define FIELD_H
#include "MonsterZone.h"
#include "SpellTrapZone.h"
#include "Graveyard.h"
#include "Deck.h"

class Field {
public:
    Field();
    void setField(int, int, int);

    MonsterZone monsterZone;
    Graveyard* graveyard;
    SpellTrapZone spellTrapZone;
    Deck deck;

private:
    float m_width;
};

#endif // FIELD_H
