#include "headers/Card.h"
#include<numeric>
#include<iterator>
#include <iostream>


Card::Card(const std::string &CardName, CardType CType, CardPlace CPlace, const std::string &CardDescription)
    :CardName(CardName)
    ,CType(CType)
    ,CPlace(CPlace)
    ,CardDescription(CardDescription)
{}

Card::~Card()
{
}

const std::string &Card::getCardName() const
{
    return CardName;
}

std::string Card::getCType() const
{
    switch (CType) {
    case CardType::MonsterCard:
        return "MonsterCard";
    case CardType::TrapCard :
        return "TrapCard";
    default:
        return "SpellCard";
    }
}

CardPlace Card::getCPlace() const
{
    return CPlace;
}

void Card::setCPlace(CardPlace newCPlace)
{
    CPlace = newCPlace;
}

const std::string &Card::getCardDescription() const
{
    return CardDescription;
}

void Card::setCard()
{

}

std::ostream &operator<<(std::ostream &out, Card &c){
    return out << "Card name: " << c.getCardName() << ", card type: " << c.getCType()  << std::endl;
}
