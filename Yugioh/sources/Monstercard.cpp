#include "headers/Monstercard.h"
#include "headers/EffectRequirement.h"

MonsterCard::MonsterCard(const std::string &cardName, int attackPoints, int defensePoints, int level, MonsterType type, 
                        MonsterKind kind, MonsterAttribute attribute,bool active, MonsterPosition position,
                        bool alreadyAttack, CardType cardType, CardLocation cardLocation, 
                        const std::string &cardDescription, std::string imagePath, bool isSummonedThisTurn)
    : Card(cardName, cardType, cardLocation, cardDescription,imagePath)
    ,attackPoints(attackPoints)
    ,defensePoints(defensePoints)
    ,type(type)
    ,monsterKind(kind)
    ,attribute(attribute)
    ,level(level)
    ,active(active)
    ,position(position)
    ,alreadyAttackedThisTurn(alreadyAttack)
    ,isSummonedThisTurn(isSummonedThisTurn)
{}

MonsterCard::~MonsterCard()
{

}

MonsterCard* MonsterCard::clone() {
    return new MonsterCard(this->cardName, this->attackPoints, this->defensePoints, this->level, this->type,
                           this->monsterKind, this->attribute, this->active, this->position, this->alreadyAttackedThisTurn,
                          this->cardType, this->cardLocation, this->cardDescription, this->imagePath);
}

bool MonsterCard::shouldBeSentToGraveyard()
{
    return false;
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

MonsterPosition MonsterCard::getPosition() const
{
    return position;
}

bool MonsterCard::getIsSummonedThisTurn() const
{
    return this->isSummonedThisTurn;
}

bool MonsterCard::getIsRepositionedThisTurn() const
{
    return this->isRepositionedThisTurn;
}

void MonsterCard::setIsRepositionThisTurn(bool isRepositioned)
{
    this->isRepositionedThisTurn = isRepositioned;
}

void MonsterCard::setIsSummonedThisTurn(bool isSummoned)
{
    this->isSummonedThisTurn = isSummoned;
}

void MonsterCard::setPosition(const MonsterPosition &newPosition)
{
    position = newPosition;
}

void MonsterCard::changePosition()
{
    const MonsterPosition oldPosition = getPosition();
    QTransform transformationMatrix;
    if(oldPosition == MonsterPosition::ATTACK)
    {
        // Change the actual position
        setPosition(MonsterPosition::FACE_UP_DEFENSE);

        this->move(this->x() - this->width / 5 , this->y() + this->height / 5 );


        // Change it on the scene
        transformationMatrix.rotate(90);
        setPixmap(pixmap().transformed(transformationMatrix));
    }
    else if(oldPosition == MonsterPosition::FACE_UP_DEFENSE)
    {
        setPosition(MonsterPosition::ATTACK);

        transformationMatrix.rotate(-90);
        setPixmap(pixmap().transformed(transformationMatrix));


        this->move(this->x() + this->width / 5 , this->y() - this->height / 5 );
    }
}

void MonsterCard::setAttackPoints(int newAttackPoints)
{
    attackPoints = newAttackPoints;
}

void MonsterCard::setDefensePoints(int newDefensePoints)
{
    defensePoints = newDefensePoints;
}

void MonsterCard::increaseAttackPoints(int increaseBy)
{
    int newPoints = this->attackPoints + increaseBy;
    this->setAttackPoints(newPoints);
}

void MonsterCard::decreaseAttackPoints(int decreaseBy) {
    int newPoints = this->attackPoints - decreaseBy;
    this->setAttackPoints(newPoints);
}

void MonsterCard::multiplyAttackPoints(float multiplyBy)
{
    int newPoints = this->attackPoints * multiplyBy;
    this->setAttackPoints(newPoints);
}

void MonsterCard::increaseDefensePoints(int increaseBy)
{
    int newPoints = this->defensePoints + increaseBy;
    this->setDefensePoints(newPoints);
}

void MonsterCard::decreaseDefensePoints(int decreaseBy) {
    int newPoints = this->defensePoints - decreaseBy;
    this->setDefensePoints(newPoints);
}

void MonsterCard::multiplyDefensePoints(float multiplyBy)
{
    int newPoints = this->defensePoints * multiplyBy;
    this->setDefensePoints(newPoints);

}

bool MonsterCard::normalSummon(MonsterPosition monsterPos){
    if (this->active == true or this->cardLocation != CardLocation :: HAND )
        return false; // unsuporeted actions
    this->active = true;
    this->position = monsterPos;
    return true;
}


bool MonsterCard::specialSummon(MonsterPosition monsterPos){
    if ( this->cardLocation == CardLocation :: DECK )
        return false;
    active = true;
    position = monsterPos;
    return true;
}

void MonsterCard::setCardMenu(bool isMonsterZoneFull,bool OpponentHaveMonsters){
    QMap<QString, bool> flagMap {{"set",false},{"summon",false},{"reposition",false},{"activate",false},{"attack",false},{"flip", false},{"attackDirectly",false}};
    EffectRequirement effectRequirement(*this);
    if (cardLocation == CardLocation::HAND && (GamePhaseExternVars::currentGamePhase == GamePhases::MAIN_PHASE1 ||
                                               GamePhaseExternVars::currentGamePhase == GamePhases::MAIN_PHASE2) &&
            !isMonsterZoneFull && !globalSummonedThisTurn){
        flagMap["set"] = true;
        flagMap["summon"] = true;
    }
    if(cardLocation == CardLocation::FIELD  && (GamePhaseExternVars::currentGamePhase == GamePhases::MAIN_PHASE1 ||
                                                GamePhaseExternVars::currentGamePhase == GamePhases::MAIN_PHASE2) &&
            !isSummonedThisTurn && !isRepositionedThisTurn){
        if(position == MonsterPosition::FACE_DOWN_DEFENSE)
            flagMap["flip"] = true;
        else
            flagMap["reposition"] = true;
    }
    if(cardLocation == CardLocation::FIELD  && GamePhaseExternVars::currentGamePhase == GamePhases::BATTLE_PHASE
            && this->alreadyAttackedThisTurn == false && position == MonsterPosition::ATTACK){
            flagMap["attack"] = true;
    }
    cardMenu->update(flagMap);
    };



void MonsterCard::setAlreadyAttackedThisTurn(bool didIAlreadyAttack)
{
    alreadyAttackedThisTurn = didIAlreadyAttack;
}




