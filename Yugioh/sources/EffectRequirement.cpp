#include "headers/EffectRequirement.h"
#include "headers/Game.h"

EffectRequirement::EffectRequirement(Card &card)
    :m_card(&card){};

EffectRequirement::~EffectRequirement(){}

const std::map<std::string, EffectRequirement::EFFECT_REQUIREMENT_MEMBER_FUNCTION_POINTER> EffectRequirement::effectReqMap = {
    //Spells
    {"Fissure",        &EffectRequirement::fissureReq}
};

bool EffectRequirement::isActivatable(const std::string &cardName)
{
    bool condition = true;
    try {
        auto effectReqFunctionPointer = effectReqMap.at(cardName);

        condition = std::invoke(effectReqFunctionPointer, this);
    } catch(std::out_of_range &e) {
        std::cerr << "Error: That card doesn't have an effect! Out of range exception from: " << e.what() << std::endl;
    }

    return condition;
}


bool EffectRequirement::fissureReq() {
    bool opponentHasMonsters = false;
    if(!GameExternVars::pOtherPlayer->field.monsterZone.isEmpty())
            opponentHasMonsters = true;

    return opponentHasMonsters;
}
