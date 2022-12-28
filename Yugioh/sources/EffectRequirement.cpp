#include "headers/EffectRequirement.h"
#include "headers/Game.h"

EffectRequirement::EffectRequirement(Card &card)
    :m_card(&card){};

EffectRequirement::~EffectRequirement(){}

const std::map<std::string, EffectRequirement::EFFECT_REQUIREMENT_MEMBER_FUNCTION_POINTER> EffectRequirement::effectReqMap = {
    //Spells
    {"Fissure",                     &EffectRequirement::fissureReq},
    {"Monster Reborn",              &EffectRequirement::monsterRebornReq},
    {"Change of Heart",             &EffectRequirement::changeofheartReq}
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

    for (Card *card : GameExternVars::pCurrentPlayer->field.graveyard->getGraveyard())
    {
        if (card->getCardType() == CardType::MONSTER_CARD){
            return true;
        }
    }
    return false;
}

bool EffectRequirement::changeofheartReq(){

    bool flag1 = false;
    if (GameExternVars::pOtherPlayer->field.monsterZone.m_monsterZone.size() == 0)
    {
        std::cout<<"return odavde"<<std::endl;
        return false;
    }
    for (Zone *zone : GameExternVars::pOtherPlayer->field.monsterZone.m_monsterZone){
        if (!zone->isEmpty() && zone->m_pCard->getCardType()== CardType::MONSTER_CARD){
            flag1 = true;
            break;
        }
    }
    if (flag1 == false)
        return false;
    for (Zone *zone1 : GameExternVars::pCurrentPlayer->field.monsterZone.m_monsterZone)
    {
        if (zone1->isEmpty())
        {
            if (flag1 == true)
                return true;
        }
    }

    return false;
}
