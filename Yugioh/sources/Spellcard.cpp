#include "headers/Spellcard.h"
#include "headers/Card.h"


SpellCard::SpellCard(SpellType type, const std::string &cardName, CardType cardType, CardLocation cardLocation, const std::string &cardDescription)
    : Card(cardName, cardType, cardLocation, cardDescription)
    ,type(type)
{}

void SpellCard::setCard()
{

}

SpellType SpellCard::getType() const
{
    return type;
}
