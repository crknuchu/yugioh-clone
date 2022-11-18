#ifndef MONSTERCARD_H
#define MONSTERCARD_H

#include "headers/Card.h"

enum class MonsterType
{
    NormalMonster,
    EffectMonster,
    RitualMonster,
    FusionMonster,
    XYZMonster,
    PendulumMonster,
    LinkMonster,
    MonsterToken
};

enum class MonsterKind{
    Aqua,
    Beast,
    BeastWarrior,
    CreatorGod,
    Dinosaur,
    DivineBeast,
    Dragon,
    Fairy,
    Fiend,
    Fish,
    Insect,
    Machine,
    Plant,
    Psychic,
    Reptile,
    Rock,
    Spellcaster,
    Warrior,
    WingedBeast

};

enum class Attribute
{
    Light,
    Dark
};


class MonsterCard : public Card
{
public:
    MonsterCard(int attackPoints, int defensePoints, MonsterType tip,MonsterKind kind, Attribute atribute, int level, const std::string &CardName, CardType CType, CardPlace CPlace, const std::string &CardDescription);

    virtual void setCard();

    int getAttackPoints() const;

    int getDefensePoints() const;

    MonsterType getTip() const;

    Attribute getAtribut() const;

    int getLevel() const;

protected:
    int attackPoints;
    int defensePoints;
    MonsterType tip;
    MonsterKind kind;
    Attribute atribute;
    int level;
};


#endif // MONSTERCARD_H
