#include "headers/EffectRequirement.h"
#include "headers/Game.h"

EffectRequirement::EffectRequirement(Card &card)
    :m_card(&card){};

EffectRequirement::~EffectRequirement(){}

const std::map<std::string, EffectRequirement::EFFECT_REQUIREMENT_MEMBER_FUNCTION_POINTER> EffectRequirement::effectReqMap = {
    //Spells
    {"Fissure",        &EffectRequirement::fissureReq},
    {"Monster Reborn", &EffectRequirement::monsterRebornReq},
    {"Hane-Hane",      &EffectRequirement::haneHaneReq},
    //Traps
    {"Reinforcements", &EffectRequirement::reinforcementsReq}
};

bool EffectRequirement::isActivatable(const std::string &cardName)
{
    bool condition = true;
    try {
        auto effectReqFunctionPointer = effectReqMap.at(cardName);

        condition = std::invoke(effectReqFunctionPointer, this);
    } catch(std::out_of_range &e) {
        std::cout << "That card doesn't have a requirement." << std::endl;
    }

    return condition;
}


bool EffectRequirement::fissureReq() {
    bool opponentHasMonsters = false;
    if(!GameExternVars::pOtherPlayer->field.monsterZone.isEmpty())
            opponentHasMonsters = true;

    return opponentHasMonsters;
}

bool EffectRequirement::monsterRebornReq(){

    bool isAnyMonsterInGraveyard = false;
    for (Card *card : GameExternVars::pCurrentPlayer->field.graveyard->getGraveyard()) {
        if (card->getCardType() == CardType::MONSTER_CARD){
            isAnyMonsterInGraveyard = true;
        }
    }

    for (Card *card : GameExternVars::pOtherPlayer->field.graveyard->getGraveyard()) {
        if (card->getCardType() == CardType::MONSTER_CARD){
            isAnyMonsterInGraveyard = true;
        }
    }

    return isAnyMonsterInGraveyard;
}

bool EffectRequirement::haneHaneReq() {
    return EffectRequirement::fissureReq();
}

bool EffectRequirement::reinforcementsReq() {
    bool currentPlayerHasMonsters = false;
    if(!GameExternVars::pCurrentPlayer->field.monsterZone.isEmpty())
            currentPlayerHasMonsters = true;

    return currentPlayerHasMonsters;
}
