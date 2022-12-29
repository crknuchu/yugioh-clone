#ifndef EFFECTREQUIREMENT_H
#define EFFECTREQUIREMENT_H

#include <iostream>
#include <map>
#include "Card.h"

class EffectRequirement {
    using EFFECT_REQUIREMENT_MEMBER_FUNCTION_POINTER = bool (EffectRequirement::*)(void);
public:
    EffectRequirement() = delete;
    EffectRequirement(Card &);
    ~EffectRequirement();

    static const std::map<std::string, EFFECT_REQUIREMENT_MEMBER_FUNCTION_POINTER> effectReqMap;
    bool isActivatable(const std::string &cardName);
private:
    Card *m_card;

    bool changeofheartReq();
    bool fissureReq();
    bool monsterRebornReq();
    bool haneHaneReq();
    bool reinforcementsReq();
    bool invigorationReq();
    bool swordOfDarkDestructionReq();
};

#endif // EFFECTREQUIREMENT_H
