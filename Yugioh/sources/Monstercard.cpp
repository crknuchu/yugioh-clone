#include "headers/Monstercard.h"


MonsterCard::MonsterCard(const std::string &cardName, int attackPoints, int defensePoints, int level, MonsterType type, MonsterKind kind, MonsterAttribute attribute,bool active,Summon position, CardType cardType, CardLocation cardLocation, const std::string &cardDescription)
    : Card(cardName, cardType, cardLocation, cardDescription)
    ,attackPoints(attackPoints)
    ,defensePoints(defensePoints)
    ,type(type)
    ,kind(kind)
    ,attribute(attribute)
    ,level(level)
    ,active(active)
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

void MonsterCard::setAttackPoints(int newAttackPoints)
{
    attackPoints = newAttackPoints;
}

void MonsterCard::setDefensePoints(int newDefensePoints)
{
    defensePoints = newDefensePoints;
}

void MonsterCard::increaseAttackPoints(int points)
{
    int newPoints = this->attackPoints+points;
    this->setAttackPoints(newPoints);
}
void MonsterCard::muliplyAttackPoints(int coef)
{
    int newPoints = this->attackPoints*coef;
    this->setAttackPoints(newPoints);
}

void MonsterCard::increaseDefensePoints(int points)
{
    int newPoints = this->defensePoints+points;
    this->setDefensePoints(newPoints);
}
void MonsterCard::muliplyDefensePoints(int coef)
{
    int newPoints = this->defensePoints*coef;
    this->setDefensePoints(newPoints);

}

void MonsterCard::normalSummon(Summon s){
    if (this->active == true or this->cardLocation != CardLocation :: HAND or s == Summon::FLIP)
        return ; // unsuporeted actions
    this->active = true;
    this->position = s;
}


void MonsterCard::specialSummon(Summon s){
    if ( this->cardLocation == CardLocation :: DECK )
        return ; // ne moze da radi ako je na terenu
    this->active = true;
    this->position = s;
}





