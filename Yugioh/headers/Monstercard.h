#ifndef MONSTERCARD_H
#define MONSTERCARD_H

#include "headers/Card.h"

enum class MonsterKind
{
    NORMAL_MONSTER,
    EFFECT_MONSTER,
    RITUAL_MONSTER,
    FUSION_MONSTER,
    XYZ_MONSTER,
    PENDULUM_MONSTER,
    LINK_MONSTER,
    TOKEN_MONSTER
};

enum class MonsterType{
    AQUA,
    BEAST,
    BEAST_WARRIOR,
    CREATOR_GOD,
    DINOSAUR,
    DIVINE_BEAST,
    DRAGON,
    FAIRY,
    FIEND,
    FISH,
    INSECT,
    MACHINE,
    PLANT,
    PSYCHIC,
    REPTILE,
    ROCK,
    SPELLCASTER,
    WARRIOR,
    WINGED_BEAST
};

enum class MonsterAttribute
{
    DARK,
    DIVINE,
    EARTH,
    FIRE,
    LIGHT,
    WATER,
    WIND
};


class MonsterCard : public Card
{
public:

    MonsterCard( const std::string &cardName,int attackPoints, int defensePoints, int level, MonsterType type, MonsterKind kind, MonsterAttribute attribute, CardType cardType, CardLocation cardLocation, const std::string &cardDescription);
    virtual ~MonsterCard();



    int getAttackPoints() const;
    int getDefensePoints() const;
    MonsterType getType() const;
    MonsterAttribute getAttribute() const;
    int getLevel() const;

protected:
    int attackPoints;
    int defensePoints;
    MonsterType type;
    MonsterKind kind;
    MonsterAttribute attribute;
    int level;
};


#endif // MONSTERCARD_H
