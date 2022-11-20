#include "headers/Trapcard.h"

TrapCard::TrapCard(TrapType type, const std::string &cardName, CardType cardType, CardLocation cardLocation, const std::string &cardDescription)
    : Card(cardName, cardType, cardLocation, cardDescription)
    ,type(type)
{}


TrapType TrapCard::getType() const
{
    return type;
}
