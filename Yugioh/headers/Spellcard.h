#ifndef SPELLCARD_H
#define SPELLCARD_H

#include "Card.h"

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
    SpellCard(SpellType type,const std::string &cardName, CardType cardType, CardLocation cardLocation, const std::string &cardDescription,bool active = false);

    ~SpellCard();

    SpellType getSpellType() const;
    std:: string getSpellTypeString()const;
    void activateSpell();
    void setCardMenu(bool isMonsterZoneFull,bool OpponentHaveMonsters) override;


protected:
    SpellType type;
    bool active;

};



#endif // SPELLCARD_H
