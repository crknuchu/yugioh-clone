#ifndef SPELLCARD_H
#define SPELLCARD_H

#include "headers/Card.h"

enum class SpellType
{
    NormalSpells,
    ContinuousSpells,
    EquipSpells,
    QuickPlaySpells,
    FieldSpells,
    RitualSpells
};

class SpellCard : public Card
{
public:
    SpellCard(SpellType Stype, const std::string &CardName, CardType CType, CardPlace CPlace, const std::string &CardDescription);

    virtual void setCard();
    SpellType getStype() const;



protected:
    SpellType Stype;

};



#endif // SPELLCARD_H
