#include "headers/EffectActivator.h"
#include "headers/Game.h"
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

    // This is actually a passive effect. Its only "activated" while Lord of D is on the field.
    // TODO: How to make it apply only while Lord of D is on the field?


    // TODO: Should we pass the "global" GameExternVars here or use them directly inside function definition?
    makeMonstersOfThisTypeUntargetable(MonsterType::DRAGON, UntargetableBy::CARD_EFFECT, CardLocation::FIELD, *GameExternVars::m_pCurrentPlayer);





    // Placeholder for generic parts testing, will be removed
    // Cards will probably be passed as an argument to the activation functions


    // returnToHand test
    MonsterCard* monsterCard2 = new MonsterCard("Lord of D", 3000, 2500, 4,
                                                MonsterType::SPELLCASTER, MonsterKind::EFFECT_MONSTER,
                                                MonsterAttribute::DARK, false, Position::ATTACK, false,
                                                CardType::MONSTER_CARD, CardLocation::HAND,
                                                "Neither player can target Dragon monsters on the field with card effects."
                                                );
    returnToHand(*monsterCard2, GamePhases::END_PHASE, *GameExternVars::m_pCurrentPlayer);


    // changeHealthPointsBy test
    changeHealthPointsBy(500, *GameExternVars::m_pCurrentPlayer);

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
void EffectActivator::makeMonstersOfThisTypeUntargetable(const MonsterType &targetType, const UntargetableBy &restrictedMechanic,
                                                         const CardLocation &cardLocation, Player &targetPlayer)
{
    /* TODO: cout for these enums isn't possible because there are no extern enum -> string maps,
             so we can currently only cout the player that this applies to. */
    std::cout << "This applies to: " << targetPlayer << std::endl;



    // TODO: Normal naming system
//    targetPlayer.setMonstersOfThisTypeUntargetable(targetType, restrictedMechanic, cardLocation, true);
}


void EffectActivator::returnToHand(Card &card, const GamePhases &inWhichGamePhase, Player &targetPlayer)
{
    std::cout << "Player " << targetPlayer.getPlayerName() << "'s card " << card.getCardName() <<
                 " will be returned to the hand in the " << GamePhaseExternVars::gamePhaseToQString.at(inWhichGamePhase).toStdString() << "." << std::endl;

//    if(currentGamePhase == inWhichGamePhase)
//        targetPlayer.deck.returnToHand(card)
}


// Maybe this is unneeded because a similar thing can exist in Player
void EffectActivator::changeHealthPointsBy(int pointChange, Player &targetPlayer) {
    // targetPlayer.changeHealthBy(pointChange);

    // The following code is only for the purpose of unified output, it can be made prettier probably.
    std::string lostOrGained = pointChange < 0 ? "lost" : "gained";

    // We want to have non-negative points for the output, since we already say "lost" or "gained" it would be weird to say lost -500 hp.
    pointChange = pointChange < 0 ? pointChange * -1 : pointChange;


    std::cout << "Player " << targetPlayer.getPlayerName() << " " << lostOrGained << " " << pointChange << " health points." << std::endl;

    emit healthPointsChanged();

}


