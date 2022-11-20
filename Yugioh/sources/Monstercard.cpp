#include "headers/Monstercard.h"


MonsterCard::MonsterCard(const std::string &cardName, int attackPoints, int defensePoints, int level, MonsterType type, MonsterKind kind, MonsterAttribute attribute, CardType cardType, CardLocation cardLocation, const std::string &cardDescription)
    : Card(cardName, cardType, cardLocation, cardDescription)
    ,attackPoints(attackPoints)
    ,defensePoints(defensePoints)
    ,type(type)
    ,kind(kind)
    ,attribute(attribute)
    ,level(level)
{
}

MonsterCard::~MonsterCard()
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

MonsterType MonsterCard::getType() const
{
    return type;
}

MonsterAttribute MonsterCard::getAttribute() const
{
    return attribute;
}

int MonsterCard::getLevel() const
{
    return level;
}








