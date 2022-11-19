#ifndef SPELLCARD_H
#define SPELLCARD_H

#include "headers/Card.h"

enum class SpellType
{
    NORMAL_SPELL,
    CONTINUOUS_SPELL,
    EQUIP_SPELL,
    QUICK_SPELL,
    FIELD_SPELL,
    RITUAL_SPELL
};

class SpellCard : public Card
{
public:
    SpellCard(SpellType type, const std::string &cardName, CardType cardType, CardLocation cardLocation, const std::string &cardDescription);

    virtual void setCard();
    SpellType getType() const;



protected:
    SpellType type;

};



#endif // SPELLCARD_H
