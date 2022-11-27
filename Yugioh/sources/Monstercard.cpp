#include "headers/Monstercard.h"


MonsterCard::MonsterCard(const std::string &cardName, int attackPoints, int defensePoints, int level, MonsterType type, MonsterKind kind, MonsterAttribute attribute,bool active,Summon position, CardType cardType, CardLocation cardLocation, const std::string &cardDescription)
    : Card(cardName, cardType, cardLocation, cardDescription)
    ,attackPoints(attackPoints)
    ,defensePoints(defensePoints)
    ,type(type)
    ,monsterKind(kind)
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

MonsterKind MonsterCard::getMonsterKind() const
{
    return monsterKind;
}

std::string MonsterCard::getMonsterKindString() const
{
    switch (monsterKind) {
    case MonsterKind::NORMAL_MONSTER:
        return "normal monster";
    case MonsterKind::EFFECT_MONSTER :
        return "effect monster";
    case MonsterKind::RITUAL_MONSTER:
        return "ritual monster";
    case MonsterKind::FUSION_MONSTER:
        return "fusion monster";
    case MonsterKind::XYZ_MONSTER:
        return "xyz monster";
    case MonsterKind::PENDULUM_MONSTER:
        return "pendulum monster";
    case MonsterKind::LINK_MONSTER:
        return "link monster";
    case MonsterKind::TOKEN_MONSTER:
        return "token monster";
    default:
        return "error:unknown monster kind";
    }
}


MonsterType MonsterCard::getMonsterType() const
{
    return type;
}


std::string MonsterCard::getMonsterTypeString() const
{
    switch (type) {
    case MonsterType::AQUA:
        return "aqua";
    case MonsterType::BEAST :
        return "beast";
    case MonsterType::BEAST_WARRIOR:
        return "beast warrior";
    case MonsterType::CREATOR_GOD:
        return "creator god";
    case MonsterType::DINOSAUR:
        return "dinosaur";
    case MonsterType::DIVINE_BEAST:
        return "divine beast";
    case MonsterType::DRAGON:
        return "dragon";
    case MonsterType::FAIRY:
        return "fairy";
    case MonsterType::FIEND:
        return "fiend";
    case MonsterType::FISH:
        return "fish";
    case MonsterType::INSECT:
        return "insect";
    case MonsterType::MACHINE:
        return "machine";
    case MonsterType::PLANT:
        return "plant";
    case MonsterType::PSYCHIC:
        return "psychic";
    case MonsterType::REPTILE:
        return "reptile";
    case MonsterType::ROCK:
        return "rock";
    case MonsterType::SPELLCASTER:
        return "spell caster";
    case MonsterType::WARRIOR:
        return "warrior";
    case MonsterType::WINGED_BEAST:
        return "winged beast";
    default:
        return "error:unknown monster type";
    }
}


MonsterAttribute MonsterCard::getAttribute() const
{
    return attribute;
}

std::string MonsterCard::getAttributeString() const
{
    switch (attribute) {
    case MonsterAttribute::DARK:
        return "dark";
    case MonsterAttribute::DIVINE :
        return "divine";
    case MonsterAttribute::EARTH:
        return "earth";
    case MonsterAttribute::FIRE:
        return "fire";
    case MonsterAttribute::LIGHT:
        return "light";
    case MonsterAttribute::WATER:
        return "water";
    case MonsterAttribute::WIND:
        return "wind";
    default:
        return "error:unknown attribute";
}
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





