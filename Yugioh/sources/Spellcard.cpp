#include "headers/Spellcard.h"
#include "headers/Card.h"


SpellCard::SpellCard(SpellType Stype, const std::string &CardName, CardType CType, CardPlace CPlace, const std::string &CardDescription)
    : Card(CardName, CType, CPlace, CardDescription)
    ,Stype(Stype)
{}

void SpellCard::setCard()
{

}

SpellType SpellCard::getStype() const
{
    return Stype;
}
