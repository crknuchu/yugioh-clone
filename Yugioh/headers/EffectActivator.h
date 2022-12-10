#ifndef EFFECTACTIVATOR_H
#define EFFECTACTIVATOR_H

#include <iostream>
#include <map>

#include "Monstercard.h"
#include "Player.h"
#include "GamePhase.h"

enum class UntargetableBy {
    CARD_EFFECT,
    MONSTER
};


class EffectActivator {
    // Our type that represents a pointer to EffectActivator member function that accept no arguments and return void
    using EFFECT_MEMBER_FUNCTION_POINTER = void(EffectActivator::*)(void);
public:
    EffectActivator();
    ~EffectActivator();
    static const std::map<std::string, EFFECT_MEMBER_FUNCTION_POINTER> effectMap;


private:
    // Private member functions

    // Monster card effect activations:
    void activateLordOfD();
    void activateMysteriousPuppeteer();
    void activateTheWickedWormBeast();
    void activateTrapMaster();
    void activateHaneHane();

    // Spell card activations:

    // Trap card activations:




    // WIP
    // Generic outcomes that make up card's effects:
    void makeMonstersOfThisTypeUntargetable(const MonsterType &, const UntargetableBy &, const CardLocation &, Player &);
    void returnToHand(const Card &, const GamePhasesEnum &);
};



#endif // EFFECTACTIVATOR_H
