#ifndef FIELD_H
#define FIELD_H
#include "MonsterZone.h"
#include "SpellTrapZone.h"
#include "Graveyard.h"
#include "Deck.h"
#include "FieldZone.h"

class Field {
public:
    Field();
    void setField(int, int, int);

    FieldZone* fieldZone;
    MonsterZone monsterZone;
    Graveyard* graveyard;
    SpellTrapZone spellTrapZone;
    Deck deck;

private:
    float m_width;
};

#endif // FIELD_H
