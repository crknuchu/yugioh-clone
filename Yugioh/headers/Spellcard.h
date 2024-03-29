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
    SpellCard(SpellType type,const std::string &cardName, CardType cardType, CardLocation cardLocation, SpellTrapPosition position, const std::string &cardDescription,std::string imagePath,bool active = false);

    SpellCard* clone() override;
    bool shouldBeSentToGraveyard() override;
    SpellType getSpellType() const;
    std::string getSpellTypeString() const;
    SpellTrapPosition getSpellPosition() const;
    void activateSpell();

    void setPosition(SpellTrapPosition newPosition);

    void setCardMenu(bool isMonsterZoneFull,bool OpponentHaveMonsters) override;

    bool getActive() const;

private:
    SpellType type;
    bool active;
    SpellTrapPosition position;



};



#endif // SPELLCARD_H
