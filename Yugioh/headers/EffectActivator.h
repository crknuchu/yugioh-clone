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
    using EFFECT_MEMBER_FUNCTION_POINTER = void (EffectActivator::*)(void);
public:
    EffectActivator() = delete;
    EffectActivator(Card &);
    ~EffectActivator();

    static const std::map<std::string, EFFECT_MEMBER_FUNCTION_POINTER> effectMap;

    // Public member functions
    Card* getCard() const; // Card* &getCard() const; ?
    void setCard(Card &);
private:
    Card *m_card; // We can't have a non pointer because Card is abstract





    // Private member functions
    // Deck 1:
    // Monster card effect activations:
    void activateLordOfD();
    void activateMysteriousPuppeteer();
    void activateTheWickedWormBeast();
    void activateTrapMaster();
    void activateHaneHane();

    // Spell card effect activations:
    void activateDarkEnergy();
    void activateInvigoration();
    void activateSogen();
    void activateAncientTelescope();
    void activateDarkHole();
    void activateDeSpell();
    void activateFissure();
    void activateMonsterReborn();
    void activateOokazi();
    void activateRemoveTrap();
    void activateTheFluteOfSummoningDragon();
    void activateTheInexperiencedSpy();

    // Trap card effect activations:
    void activateUltimateOffering();
    void activateCastleWalls();
    void activateJustDesserts();
    void activateReinforcements();
    void activateReverseTrap();
    void activateTrapHole();
    void activateTwoProngedAttack();





    // WIP
    // Generic outcomes that make up card's effects:
    void makeMonstersOfThisTypeUntargetable(const MonsterType &, const UntargetableBy &, const CardLocation &, Player &);
    void returnToHand(const GamePhases &, Player &);
};



#endif // EFFECTACTIVATOR_H
