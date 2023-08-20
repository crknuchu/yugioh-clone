#ifndef FIELD_H
#define FIELD_H
#include "Deck.h"
#include "FieldZone.h"
#include "Graveyard.h"
#include "MonsterZone.h"
#include "SpellTrapZone.h"

class Field {
public:
  Field();
  void setField(int, int, int);

  FieldZone *fieldZone; // moralo je zbog qgraphihcs item pokazivac
  MonsterZone monsterZone;
  Graveyard *graveyard; // isto kao gore
  SpellTrapZone spellTrapZone;
  //    Graveyard graveyard;
  Deck deck;

private:
  float m_width;
};

#endif // FIELD_H
