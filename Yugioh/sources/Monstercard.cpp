#include "headers/Monstercard.h"

MonsterCard::MonsterCard(int attackPoints, int defensePoints, MonsterType tip,MonsterKind kind, Attribute atribut, int level, const std::string &CardName, CardType CType, CardPlace CPlace, const std::string &CardDescription)
    : Card(CardName, CType, CPlace, CardDescription)
    ,attackPoints(attackPoints)
    ,defensePoints(defensePoints)
    ,tip(tip)
    ,kind(kind)
    ,atribute(atribut)
    ,level(level)
{}

void MonsterCard::setCard()
{

}


int MonsterCard::getAttackPoints() const
{
    return attackPoints;
}

int MonsterCard::getDefensePoints() const
{
    return defensePoints;
}

MonsterType MonsterCard::getTip() const
{
    return tip;
}

Attribute MonsterCard::getAtribut() const
{
    return atribute;
}

int MonsterCard::getLevel() const
{
    return level;
}








