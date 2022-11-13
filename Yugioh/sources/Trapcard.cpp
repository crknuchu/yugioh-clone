#include "headers/Trapcard.h"

TrapCard::TrapCard(TrapType Ttype, const std::string &CardName, CardType CType, CardPlace CPlace, const std::string &CardDescription)
    : Card(CardName, CType, CPlace, CardDescription)
    ,Ttype(Ttype)
{}

void TrapCard::setCard()
{

}

TrapType TrapCard::getTtype() const
{
    return Ttype;
}
