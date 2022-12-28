#include "headers/EffectActivator.h"
#include "headers/Game.h"
#include "headers/EffectRequirement.h"
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
    {"Ancient Telescope",               &EffectActivator::activateAncientTelescope},
    {"Card Destruction",                &EffectActivator::activateCardDestruction},
    {"Dark Energy",                     &EffectActivator::activateDarkEnergy},
    {"Dark Hole",                       &EffectActivator::activateDarkHole},
    {"De-Spell",                        &EffectActivator::activateDeSpell},
    {"Dian Keto the Cure Master",       &EffectActivator::activateDianKetoTheCureMaster},
    {"Fissure",                         &EffectActivator::activateFissure},
    {"Invigoration",                    &EffectActivator::activateInvigoration},
    {"Monster Reborn",                  &EffectActivator::activateMonsterReborn},
    {"Ookazi",                          &EffectActivator::activateOokazi},
    {"Remove Trap",                     &EffectActivator::activateRemoveTrap},
    {"Sogen",                           &EffectActivator::activateSogen},
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

void EffectActivator::activateEffect(const std::string &cardName)
{
    try {
        auto effectFunctionPointer = effectMap.at(cardName);

        // (effectActivator.*funcPointer)(); // This is the same as the invoke call below.
        // If the first argument is a pointer to member func, invoke expects an object that owns it to be a first argument.
        std::invoke(effectFunctionPointer, this);
    } catch(std::out_of_range &e) {
        std::cerr << "Error: That card doesn't have an effect! Out of range exception from: " << e.what() << std::endl;
    }
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
        // Serialization and deserialization ?
    makeMonstersOfThisTypeUntargetable(MonsterType::DRAGON, UntargetableBy::CARD_EFFECT, CardLocation::FIELD, *GameExternVars::pCurrentPlayer);




    // Test returnToHand
    returnToHand(*(this->getCard()), GamePhases::END_PHASE, *GameExternVars::pCurrentPlayer);


//    // changeLifePointsBy test
    changeHealthPointsBy(-500, *GameExternVars::pCurrentPlayer);

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
    MonsterCard* targetedMonster = findHighestATKMonster(*GameExternVars::pOtherPlayer);
    Zone* zoneWithTargetedMonster = GameExternVars::pOtherPlayer->field.monsterZone.getZone(targetedMonster);
    GameExternVars::pOtherPlayer->field.monsterZone.removeFromMonsterZone(zoneWithTargetedMonster);
    GameExternVars::pOtherPlayer->m_hand.addToHand(*targetedMonster);
}

// Spells
void EffectActivator::activateDarkEnergy()
{

}

void EffectActivator::activateInvigoration()
{
//An EARTH monster equipped with this card
//increases its ATK by 400 points and decreases its DEF by 200 points.


}

void EffectActivator::activateSogen()
{

}

void EffectActivator::activateAncientTelescope()
{

}

void EffectActivator::activateCardDestruction() {
    float currentPlayerHandSize = GameExternVars::pCurrentPlayer->m_hand.size();
    for(Card* card : GameExternVars::pCurrentPlayer->m_hand.getHand()) {
        GameExternVars::pCurrentPlayer->discard(*card);
    }

    GameExternVars::pCurrentPlayer->drawCards(currentPlayerHandSize);

    float opponentHandSize = GameExternVars::pOtherPlayer->m_hand.size();
    for(Card* card : GameExternVars::pOtherPlayer->m_hand.getHand()) {
        GameExternVars::pOtherPlayer->discard(*card);
    }
    GameExternVars::pOtherPlayer->drawCards(opponentHandSize);
}

void EffectActivator::activateDarkHole()
{
    for(Zone* zone : GameExternVars::pCurrentPlayer->field.monsterZone.m_monsterZone) {
        if(!zone->isEmpty())
            GameExternVars::pCurrentPlayer->sendToGraveyard(*zone->m_pCard, zone);
    }

    for(Zone* zone : GameExternVars::pOtherPlayer->field.monsterZone.m_monsterZone) {
        if(!zone->isEmpty())
            GameExternVars::pOtherPlayer->sendToGraveyard(*zone->m_pCard, zone);
    }
}

void EffectActivator::activateDeSpell()
{

}

void EffectActivator::activateDianKetoTheCureMaster() {
    changeHealthPointsBy(1000, *GameExternVars::pCurrentPlayer);
}

void EffectActivator::activateFissure()
{
    std::vector<Zone *>monsters = GameExternVars::pOtherPlayer->field.monsterZone.m_monsterZone;
    std::cout<<GameExternVars::pOtherPlayer->getPlayerName();
    int lowestATK = 100000;
    Card *destroyCard = nullptr;
    Zone *destroyZone = nullptr;


    for (Zone *zone : monsters)
    {
        if (zone->isEmpty())
            continue;
        if (!zone->isEmpty() && zone->m_pCard->getCardType() == CardType::MONSTER_CARD)
        {

            MonsterCard *m = dynamic_cast<MonsterCard *>(zone->m_pCard);


            if (m->getAttackPoints() < lowestATK)
            {
                lowestATK = m->getAttackPoints();
                destroyCard = zone->m_pCard;
                destroyZone = zone;
            }

        }
    }
    if (destroyCard == nullptr || destroyZone == nullptr)
        return;
    GameExternVars::pOtherPlayer->sendToGraveyard(*destroyCard, destroyZone);

}

void EffectActivator::activateMonsterReborn()
{
    //we want to reborn strongest monster
    MonsterCard* strongestMonsterInEitherGraveyard = nullptr;
    int whichGraveyard = 1;
    for(Card* card : GameExternVars::pCurrentPlayer->field.graveyard->getGraveyard()) {
        if(card->getCardType() == CardType::MONSTER_CARD) {
            MonsterCard* monsterInGraveyard = static_cast<MonsterCard*>(card);
            if(!strongestMonsterInEitherGraveyard ||
                    strongestMonsterInEitherGraveyard->getAttackPoints() < monsterInGraveyard->getAttackPoints())
                strongestMonsterInEitherGraveyard = monsterInGraveyard;
        }
    }

    for(Card* card : GameExternVars::pOtherPlayer->field.graveyard->getGraveyard()) {
        if(card->getCardType() == CardType::MONSTER_CARD) {
            MonsterCard* monsterInGraveyard = static_cast<MonsterCard*>(card);
            if(!strongestMonsterInEitherGraveyard ||
                    strongestMonsterInEitherGraveyard->getAttackPoints() < monsterInGraveyard->getAttackPoints()) {
                strongestMonsterInEitherGraveyard = monsterInGraveyard;
                whichGraveyard = 2;
            }
        }
    }

    whichGraveyard == 1 ?
                GameExternVars::pCurrentPlayer->field.graveyard->removeFromGraveyard(*strongestMonsterInEitherGraveyard)
              : GameExternVars::pOtherPlayer->field.graveyard->removeFromGraveyard(*strongestMonsterInEitherGraveyard);

    GameExternVars::pCardToBePlacedOnField = strongestMonsterInEitherGraveyard;
    GameExternVars::pCurrentPlayer->field.monsterZone.colorFreeZones();
}

void EffectActivator::activateOokazi()
{
    changeHealthPointsBy(-800, *GameExternVars::pOtherPlayer);
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
    MonsterCard* strongestMonster;
    if(m_card->getPlayerThatSetThisCard() == 1)
        strongestMonster = findHighestATKMonster(*GameExternVars::pCurrentPlayer);
    else
        strongestMonster = findHighestATKMonster(*GameExternVars::pOtherPlayer);

    strongestMonster->setAttackPoints(strongestMonster->getAttackPoints() + 500);
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


void EffectActivator::returnToHand(Card &targetCard, const GamePhases &inWhichGamePhase, Player &targetPlayer)
{
    std::cout << "Player " << targetPlayer.getPlayerName() << "'s card " << getCard()->getCardName() <<
                 " will be returned to the hand in the " << GamePhaseExternVars::gamePhaseToQString.at(inWhichGamePhase).toStdString() << "." << std::endl;


    /* FIXME:
     * This can't be implemented like this, because it will only check if its
     * the target gamephase once when we call returnToHand
     * Instead, we need to somehow wait on it with slots and signals maybe? */
    if(GamePhaseExternVars::currentGamePhase == inWhichGamePhase)
        targetPlayer.m_hand.addToHand(targetCard);
}

void EffectActivator::destroyCard(Card &targetCard, Player &targetPlayer)
{
    targetPlayer.sendToGraveyard(targetCard);
}

void EffectActivator::destroyCards(std::vector<Card*> &targetCards, Player &targetPlayer)
{
    for(Card* pCard : targetCards)
    {
        destroyCard(*pCard, targetPlayer);
    }
}

void EffectActivator::excavateCards(int numberOfCards, Player &targetPlayer)
{
    // FIXME: Why would std::array require that numberOfCards be a constexpr?
        // std::array<Card*, numberOfCards> cardArray;

    Card* excavatedCards[numberOfCards];
    for (int i = 0; i < numberOfCards; i++)
        excavatedCards[i] = targetPlayer.field.deck[i]; // TODO: Is there a better way?

    //    emit displayExcavatedCards(excavatedCards);
}

void EffectActivator::revealCardsInHand(int numberOfCards, Player &targetPlayer)
{
    std::vector<Card *> hand = targetPlayer.m_hand.getHand();
    for(Card* card : hand)
        std::cout << *card << std::endl;
    if((unsigned long)numberOfCards > hand.size())
    {
        std::cerr << "Number of cards passed to revealCardsInHand() is bigger than the actual number of cards in the hand." << std::endl;
        return;
    }

    /* TODO
     * For now, we reveal first numberOfCards cards in hand.
     * In the future, there needs to be a system for opponent player to select which ones he wants to reveal.
     * It would probably be similar to our Attack slot, where we color proper cards and wait for a click. */

    std::vector<Card *> selectedCards;
    std::copy_n(begin(hand), numberOfCards, std::back_inserter(selectedCards));

    std::cout << "Test: Selected cards: " << std::endl;
    for(Card *card : selectedCards)
        std::cout << card->getCardName() << std::endl;
    // emit displayCards(selectedCards);
}

bool EffectActivator::isCardOnField(Card &targetCard, Player &targetPlayer)
{
    // TODO: MonsterZone, SpellTrapZone and other "zones" could have a method for searching if card is in them?

//    MonsterZone monsterZone(targetPlayer.monsterZone); // TODO: This way of copying vs vec1 = vec2
//    for(Zone *zone : monsterZone)
//    {
//        if(!zone->isEmpty())
//        {
//            if(zone->*m_pCard.getCardName() == targetCard.getCardName())
//                return true;
//        }
//    }
//    return false;

    // FIXME: This is only checking the MonsterZone, what if the card is a Spell or a Trap...
}




std::vector<Card *> EffectActivator::returnPlayerGraveyard(Player &targetPlayer)
{
    return targetPlayer.field.graveyard->getGraveyard();
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

std::vector<MonsterCard *> EffectActivator::findLowestATKMonsters(Player &targetPlayer)
{
    // TODO: A more functional way (copy_if) for this

//    MonsterZone monsterZone(targetPlayer.monsterZone); // TODO: This way of copying vs vec1 = vec2

//    // TODO: This should be in MonsterZone class probably
//    std::vector<MonsterCard> monsters;
//    for(auto zone : monsterZone)
//    {
//        if(!zone->isEmpty())
//        {
//            monsters.push_back(*(zone->m_pCard));
//        }
//    }




//    std::vector<MonsterCard *> lowestATKMonsters;
//    int minAttackPoints = INT_MAX;
//    for(MonsterCard &monster : monsters)
//    {
//        int currentMonsterAttackPoints = monster.getAttackPoints();
//        if(currentMonsterAttackPoints <= minAttackPoints)
//            minAttackPoints = currentMonsterAttackPoints;
//    }

//    for(MonsterCard &monster : monsters)
//    {
//        if(monster.getAttackPoints() == minAttackPoints)
//            lowestATKMonsters.push_back(&monster);
//    }

//    return lowestATKMonsters;
}

MonsterCard* EffectActivator::findHighestATKMonster(Player &targetPlayer)
{
    MonsterCard* highestATKMonster = nullptr;

    for(Zone* zone : targetPlayer.field.monsterZone.m_monsterZone) {
        if(!zone->isEmpty()){
            MonsterCard* monster = static_cast<MonsterCard*>(zone->m_pCard);
            if(!highestATKMonster || monster->getAttackPoints() > highestATKMonster->getAttackPoints())
                highestATKMonster = monster;
        }
    }

    return highestATKMonster;
}

std::vector<MonsterCard *> EffectActivator::findFaceUpMonsters(Player &targetPlayer)
{
//    MonsterZone monsterZone(targetPlayer.monsterZone); // Copy constructor vs =

//    // TODO: This should be in MonsterZone class maybe
//    std::vector<MonsterCard> faceUpMonsters;
//    for(auto zone : monsterZone)
//    {
//        if(!zone->isEmpty())
//        {
//            Card cardInZone = *(zone->m_pCard);
//            if (cardInZone.getPosition != "SET")
//                faceUpMonsters.push_back(cardInZone);
//        }
//    }
}

void EffectActivator::changeHealthPointsBy(int pointChange, Player &targetPlayer) {
    unsigned currentPlayerLifePoints = targetPlayer.getPlayerLifePoints();

    std::cout << "currentPlayerLifePoints: " << currentPlayerLifePoints << std::endl;

    // This shouldn't be unsigned because it goes to UINT_MAX if its subtracted below 0.
    int newHealthPoints = currentPlayerLifePoints + pointChange;
    newHealthPoints > 0 ? targetPlayer.setPlayerLifePoints(newHealthPoints) : emit gameEnded(targetPlayer);

    // The following code is only for the purpose of unified output, it can be made prettier probably.
    std::string lostOrGained = pointChange < 0 ? "lost" : "gained";

    // We want to have non-negative points for the output, since we already say "lost" or "gained" it would be weird to say lost -500 hp.
    pointChange = pointChange < 0 ? pointChange * -1 : pointChange;

    std::cout << "Player " << targetPlayer.getPlayerName() << " " << lostOrGained << " " << pointChange << " health points." << std::endl;
    emit lifePointsChanged(targetPlayer);
}


