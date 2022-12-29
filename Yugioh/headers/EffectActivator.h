#ifndef EFFECTACTIVATOR_H
#define EFFECTACTIVATOR_H

#include <iostream>
#include <map>

#include "Monstercard.h"
#include "Player.h"
#include "GamePhase.h"
#include <QObject>

enum class UntargetableBy {
    CARD_EFFECT,
    MONSTER
};



class EffectActivator : public QObject {
   Q_OBJECT
   
    // Our type that represents a pointer to EffectActivator member function that accept no arguments and return void
    using EFFECT_MEMBER_FUNCTION_POINTER = void (EffectActivator::*)(bool);
public:
    EffectActivator() = delete;
    EffectActivator(Card &);
    ~EffectActivator();

    static const std::map<std::string, EFFECT_MEMBER_FUNCTION_POINTER> effectMap;
    void activateEffect(const std::string &cardName, bool isOpponentActivating);


    // Public member functions
    Card* getCard() const; // Card* &getCard() const; ?
    void setCard(Card &);
private:
    // TODO: If this is of type card it gives us problems with methods that need a Card's child class
    Card *m_card; // We can't have a non pointer because Card is abstract


    // Private member functions
    // Deck 1:
    // Monster card effect activations:
    void activateLordOfD(bool isOpponentActivating);
    void activateMysteriousPuppeteer(bool isOpponentActivating);
    void activateTheWickedWormBeast(bool isOpponentActivating);
    void activateTrapMaster(bool isOpponentActivating);
    void activateHaneHane(bool isOpponentActivating);

    // Spell card effect activations:
    void activateCardDestruction(bool isOpponentActivating);
    void activateDarkEnergy(bool isOpponentActivating);
    void activateInvigoration(bool isOpponentActivating);
    void activateSogen(bool isOpponentActivating);
    void activateAncientTelescope(bool isOpponentActivating);
    void activateDarkHole(bool isOpponentActivating);
    void activateDeSpell(bool isOpponentActivating);
    void activateDianKetoTheCureMaster(bool isOpponentActivating);
    void activateFissure(bool isOpponentActivating);
    void activateMonsterReborn(bool isOpponentActivating);
    void activateOokazi(bool isOpponentActivating);
    void activateRemoveTrap(bool isOpponentActivating);
    void activateTheFluteOfSummoningDragon(bool isOpponentActivating);
    void activateTheInexperiencedSpy(bool isOpponentActivating);

    // Trap card effect activations:
    void activateUltimateOffering(bool isOpponentActivating);
    void activateCastleWalls(bool isOpponentActivating);
    void activateJustDesserts(bool isOpponentActivating);
    void activateReinforcements(bool isOpponentActivating);
    void activateReverseTrap(bool isOpponentActivating);
    void activateTrapHole(bool isOpponentActivating);
    void activateTwoProngedAttack(bool isOpponentActivating);



    // WIP
    // Generic outcomes that make up card's effects:
    void changeHealthPointsBy(int, Player &);

    // TODO: Does every method here need a targetPlayer in order to differentiate whose card we need to check
    void makeMonstersOfThisTypeUntargetable(const MonsterType &type, const UntargetableBy &forbiddenMechanic, const CardLocation &where, Player &targetPlayer);
    void returnToHand(Card &targetCard, const GamePhases &targetGamePhase, Player &targetPlayer);
    void destroyCard(Card &targetCard, Player &targetPlayer);
    void destroyCards(std::vector<Card*> &targetCards, Player &targetPlayer);
    void excavateCards(int numberOfCards, Player &targetPlayer);
    void revealCardsInHand(int numberOfCards, Player &targetPlayer);
    bool isCardOnField(Card &targetCard, Player &targetPlayer);
    std::vector<Card*> returnPlayerGraveyard(Player &targetPlayer);


    void increaseATK(MonsterCard &targetMonster, int increaseBy);
    void increaseDEF(MonsterCard &targetMonster, int increaseBy);
    void decreaseATK(MonsterCard &targetMonster, int decreaseBy);
    void decreaseDEF(MonsterCard &targetMonster, int decreaseBy);
    std::vector<MonsterCard*> findLowestATKMonsters(Player &targetPlayer); // MonsterCard* because we want a pointer to the actual cards
    MonsterCard* findHighestATKMonster(Player &targetPlayer);
    /* This could be void and instead emit a signal that would color the avaliable face-up monsters.
       Or it could return a vector like it does now, and then we can do the above in the card that calls this. */
    std::vector<MonsterCard*> findFaceUpMonsters(Player &targetPlayer);
signals:
    void lifePointsChanged(Player &);
    void gameEnded(Player &loser);
};


#endif // EFFECTACTIVATOR_H
