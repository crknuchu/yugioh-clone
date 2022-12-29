#ifndef MONSTERCARD_H
#define MONSTERCARD_H

#include "headers/Card.h"
#include "headers/GamePhase.h"

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

enum class Position{
    ATTACK,
    DEFENSE,
    NONE
};




class MonsterCard : public Card
{
public:

    MonsterCard( const std::string &cardName,int attackPoints, int defensePoints, int level, MonsterType type,
                 MonsterKind kind, MonsterAttribute attribute,bool active,Position position,bool alreadyAttack,
                 CardType cardType, CardLocation cardLocation, const std::string &cardDescription,bool summonedThisTurn = false);
     ~MonsterCard();

    int getAttackPoints() const;
    int getDefensePoints() const;
    MonsterType getMonsterType() const;
    std::string getMonsterTypeString() const;
    MonsterKind getMonsterKind()const;
    std::string getMonsterKindString()const;
    MonsterAttribute getAttribute() const;
    std::string getAttributeString() const;
    int getLevel() const;

    void setAttackPoints(int newAttackPoints);
    void setDefensePoints(int newDefensePoints);



    //methods to be called with the appropriate spell/trap card
    void increaseAttackPoints(int points);
    void muliplyAttackPoints(int coef);

    void increaseDefensePoints(int points);
    void muliplyDefensePoints(int coef);

    bool normalSummon(Position position);
    bool specialSummon(Position position);


    void setCardMenu(bool isMonsterZoneFull,bool doesOpponentHaveMonsters) override;

private:
    int attackPoints;
    int defensePoints;
    MonsterType type;
    MonsterKind monsterKind;
    MonsterAttribute attribute;
    int level;
    bool active;
    Position position;
    bool alreadyAttack;
    bool summonedThisTurn;

};




#endif // MONSTERCARD_H
