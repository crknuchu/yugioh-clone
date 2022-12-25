#ifndef MONSTERCARD_H
#define MONSTERCARD_H

#include "headers/Card.h"
#include "headers/GamePhase.h"
#include <map>

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
                 CardType cardType, CardLocation cardLocation, const std::string &cardDescription,std::string imagePath,bool summonedThisTurn = false);

    MonsterCard(MonsterCard&);
    virtual ~MonsterCard();

    int getAttackPoints() const;
    int getDefensePoints() const;
    MonsterType getMonsterType() const;
    std::string getMonsterTypeString() const;
    MonsterKind getMonsterKind()const;
    std::string getMonsterKindString()const;
    MonsterAttribute getAttribute() const;
    std::string getAttributeString() const;
    int getLevel() const;
    Position getPosition() const;

    void setAttackPoints(int newAttackPoints);
    void setDefensePoints(int newDefensePoints);

    //methods to be called with the appropriate spell/trap card
    void increaseAttackPoints(int increaseBy);
    void decreaseAttackPoints(int decreaseBy);
    void multiplyAttackPoints(float multiplyBy);

    void increaseDefensePoints(int increaseBy);
    void decreaseDefensePoints(int decreaseBy);
    void multiplyDefensePoints(float multiplyBy);

    bool normalSummon(Position position);
    bool specialSummon(Position position);


    void setCardMenu() override;

    static const std::map<Position, std::string> positionEnumToString;

protected:
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
