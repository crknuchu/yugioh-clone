#include "headers/EffectActivator.h"
#include "headers/Game.h"
// Maybe unneeded
//enum class PhasePart {
//    BEGINNING,
//    END
//};

EffectActivator::EffectActivator(Card &card)
    : m_card(&card)
{}

EffectActivator::~EffectActivator() {}

const std::map<std::string, EffectActivator::EFFECT_MEMBER_FUNCTION_POINTER> EffectActivator::effectMap = {
    // Monsters
    {"Lord of D",               &EffectActivator::activateLordOfD},
    {"Mysterious Puppeteer",    &EffectActivator::activateMysteriousPuppeteer},
    {"The Wicked Worm Beast",   &EffectActivator::activateTheWickedWormBeast},
    {"Trap Master",             &EffectActivator::activateTrapMaster},
    {"Hane-Hane",               &EffectActivator::activateHaneHane},

    // Spells
    {"Dark Energy",                     &EffectActivator::activateDarkEnergy},
    {"Invigoration",                    &EffectActivator::activateInvigoration},
    {"Sogen",                           &EffectActivator::activateSogen},
    {"Ancient Telescope",               &EffectActivator::activateAncientTelescope},
    {"Dark Hole",                       &EffectActivator::activateDarkHole},
    {"De-Spell",                        &EffectActivator::activateDeSpell},
    {"Fissure",                         &EffectActivator::activateFissure},
    {"Monster Reborn",                  &EffectActivator::activateMonsterReborn},
    {"Ookazi",                          &EffectActivator::activateOokazi},
    {"Remove Trap",                     &EffectActivator::activateRemoveTrap},
    {"The Flute of Summoning Dragon",   &EffectActivator::activateTheFluteOfSummoningDragon},
    {"The Inexperienced Spy",           &EffectActivator::activateTheInexperiencedSpy},

    // Traps
    {"Ultimate Offering",   &EffectActivator::activateUltimateOffering},
    {"Castle Walls",        &EffectActivator::activateCastleWalls},
    {"Just Desserts",       &EffectActivator::activateJustDesserts},
    {"Reinforcements",      &EffectActivator::activateReinforcements},
    {"Reverse Trap",        &EffectActivator::activateReverseTrap},
    {"Trap Hole",           &EffectActivator::activateTrapHole},
    {"Two-Pronged Attack",  &EffectActivator::activateTwoProngedAttack}
};

Card* EffectActivator::getCard() const {
    return m_card;
}

void EffectActivator::setCard(Card &card) {
    m_card = &card;
}



// Card effect activation functions:
// Monsters
void EffectActivator::activateLordOfD() {
    /* Neither player can target Dragon monsters on the field with card effects. */
    std::cout << "Lord of D's effect has been activated!" << std::endl;

    // This is actually a passive effect. Its only "activated" while Lord of D is on the field.
    // TODO: How to make it apply only while Lord of D is on the field?


    // TODO: Should we pass the "global" GameExternVars here or use them directly inside function definition?
    makeMonstersOfThisTypeUntargetable(MonsterType::DRAGON, UntargetableBy::CARD_EFFECT, CardLocation::FIELD, *GameExternVars::m_pCurrentPlayer);




    // Test returnToHand
    returnToHand(*(this->getCard()), GamePhases::END_PHASE, *GameExternVars::m_pCurrentPlayer);


    // Test increaseATK
    // FIXME: We can't pass Card to this function because we need a MonsterCard
//    increaseATK(, 500);
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

// Spells
void EffectActivator::activateDarkEnergy()
{

}

void EffectActivator::activateInvigoration()
{

}

void EffectActivator::activateSogen()
{

}

void EffectActivator::activateAncientTelescope()
{

}

void EffectActivator::activateDarkHole()
{

}

void EffectActivator::activateDeSpell()
{

}

void EffectActivator::activateFissure()
{

}

void EffectActivator::activateMonsterReborn()
{

}

void EffectActivator::activateOokazi()
{

}

void EffectActivator::activateRemoveTrap()
{

}

void EffectActivator::activateTheFluteOfSummoningDragon()
{

}

void EffectActivator::activateTheInexperiencedSpy()
{

}

// Traps
void EffectActivator::activateUltimateOffering()
{

}

void EffectActivator::activateCastleWalls()
{

}

void EffectActivator::activateJustDesserts()
{

}

void EffectActivator::activateReinforcements()
{

}

void EffectActivator::activateReverseTrap()
{

}

void EffectActivator::activateTrapHole()
{

}

void EffectActivator::activateTwoProngedAttack()
{

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


/* TODO: This should probably accept Card &targetCard as a parameter because there probably
         exists an effect that returns a card other than itself to the hand. */
void EffectActivator::returnToHand(Card &targetCard, const GamePhases &inWhichGamePhase, Player &targetPlayer)
{
    std::cout << "Player " << targetPlayer.getPlayerName() << "'s card " << getCard()->getCardName() <<
                 " will be returned to the hand in the " << GamePhaseExternVars::gamePhaseToQString.at(inWhichGamePhase).toStdString() << "." << std::endl;

//    if(currentGamePhase == inWhichGamePhase)
    //        targetPlayer.deck.returnToHand(card)
}

void EffectActivator::destroyCard(Card &targetCard/*, Player &targetPlayer, CardList &cards*/)
{
    // targetPlayer->sendToGraveyard(card);
}

void EffectActivator::excavateCards(int numberOfCards, Player &targetPlayer)
{
    // FIXME: Why would std::array require that numberOfCards be a constexpr?
//    std::array<Card*, numberOfCards> cardArray;

    Card* excavatedCards[numberOfCards];
//    for (unsigned int i = 0; i < numberOfCards; i++)
//        cardArray[i] = targetPlayer.deck[i];  // TODO: Is there a better way?

//    emit displayExcavatedCards(cardArray);
}


void EffectActivator::increaseATK(MonsterCard &targetCard, int increaseBy)
{
    // TODO: Currently there is an implicit cast from unsigned to int, maybe change it in Card class
    targetCard.increaseAttackPoints(increaseBy);
}

void EffectActivator::increaseDEF(MonsterCard &targetCard, int increaseBy)
{
    targetCard.increaseDefensePoints(increaseBy);
}

void EffectActivator::decreaseATK(MonsterCard &targetCard, int decreaseBy)
{
    targetCard.decreaseAttackPoints(decreaseBy);
}

void EffectActivator::decreaseDEF(MonsterCard &targetCard, int decreaseBy)
{
    targetCard.decreaseDefensePoints(decreaseBy);
}


