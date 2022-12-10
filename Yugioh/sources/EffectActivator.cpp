#include "headers/EffectActivator.h"

// Maybe unneeded
//enum class PhasePart {
//    BEGINNING,
//    END
//};


EffectActivator::EffectActivator() {}
EffectActivator::~EffectActivator() {}

const std::map<std::string, EffectActivator::EFFECT_MEMBER_FUNCTION_POINTER> EffectActivator::effectMap = {
    {"Lord of D",               &EffectActivator::activateLordOfD},
    {"Mysterious Puppeteer",    &EffectActivator::activateMysteriousPuppeteer},
    {"The Wicked Worm Beast",   &EffectActivator::activateTheWickedWormBeast},
    {"Trap Master",             &EffectActivator::activateTrapMaster},
    {"Hane-Hane",               &EffectActivator::activateHaneHane}
};


// Monster effect activations:
void EffectActivator::activateLordOfD() {
    /* Neither player can target Dragon monsters on the field with card effects. */
    std::cout << "Lord of D's effect has been activated!" << std::endl;


    /* Placeholder, maybe in the future EffectActivator can inherit Player,
       then we wouldn't have to pass a player variable to our methods,
       we could use exact player
    */
    /* The other way is maybe to use m_pCurrentPlayer which would have to be a static variable */
    Player p1;




    // This is actually a passive effect. Its only "activated" while Lord of D is on the field.
    makeMonstersOfThisTypeUntargetable(MonsterType::DRAGON, UntargetableBy::CARD_EFFECT, CardLocation::FIELD, p1);
}

void EffectActivator::activateMysteriousPuppeteer() {
    /* Each time you or your opponent Normal Summons or Flip Summons a monster,
     * increase your Life Points by 500 points. */
    std::cout << "Mysterious Puppeteer's effect has been activated!" << std::endl;
    // ...
}

void EffectActivator::activateTheWickedWormBeast() {
    std::cout << "The Wicked Worm Beast's effect has been activated!" << std::endl;
    // ...
}

void EffectActivator::activateTrapMaster() {
    std::cout << "Trap Master's effect has been activated!" << std::endl;
    // ...
}

void EffectActivator::activateHaneHane() {
    std::cout << "Hane-Hane's effect has been activated!" << std::endl;
    // ...
}



// Generic parts of effects:
// TODO: Methods (for example, setTargetable) used in these methods have to be implemented in the future.

// TODO: Variable arguments (1 or 2 players)
void EffectActivator::makeMonstersOfThisTypeUntargetable(const MonsterType &targetType, const UntargetableBy &restrictedMechanic, const CardLocation &cardLocation, Player &targetPlayer)
{
    // TODO: Normal naming system
    // targetPlayer.setMonsterOfThisTypeTargetable(targetType, restrictedMechanic, cardLocation, false);
}


void EffectActivator::returnToHand(const Card &card, const GamePhasesEnum &inWhichPhase)
{
//    if(currentGamePhase == inWhichPhase)
//        currentPlayer.deck.return
}


