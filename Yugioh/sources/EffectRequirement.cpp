#include "headers/EffectRequirement.h"
#include "headers/Game.h"

EffectRequirement::EffectRequirement(Card &card)
    :m_card(&card){};

EffectRequirement::~EffectRequirement(){}

const std::map<std::string, EffectRequirement::EFFECT_REQUIREMENT_MEMBER_FUNCTION_POINTER> EffectRequirement::effectReqMap = {
    //Spells

    {"Fissure",                     &EffectRequirement::fissureReq},
    {"Monster Reborn",              &EffectRequirement::monsterRebornReq},
    {"Change of Heart",             &EffectRequirement::changeofheartReq},
    {"Hane-Hane",                   &EffectRequirement::haneHaneReq},
    {"Invigoration",                &EffectRequirement::invigorationReq},
    {"Sword Of Dark Destruction",   &EffectRequirement::swordOfDarkDestructionReq},
    {"Book of Secret Arts",         &EffectRequirement::bookOfSecretArtsReq},
    {"Yami",                        &EffectRequirement::yamiReq},
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

bool EffectRequirement::yamiReq(){
    std::vector<Zone *>monsters = GameExternVars::pCurrentPlayer->field.monsterZone.m_monsterZone;

    for (Zone *zone : monsters)
    {
        if (zone->isEmpty())
            continue;
        
        MonsterCard *m = dynamic_cast<MonsterCard *>(zone->m_pCard);
        if (!zone->isEmpty() && m->getCardType() == CardType::MONSTER_CARD)
        {
            if(m->getMonsterType() == MonsterType::SPELLCASTER)
                return true;
            else if(m->getMonsterType() == MonsterType::FIEND)
                return true;
            else if(m->getMonsterType() == MonsterType::FAIRY)
                return true;
            else
                return false;
        }
        else 
            return false;
    }
}

bool EffectRequirement::bookOfSecretArtsReq(){
    std::vector<Zone *>monsters = GameExternVars::pCurrentPlayer->field.monsterZone.m_monsterZone;

    for (Zone *zone : monsters)
    {
        if (zone->isEmpty())
            continue;
        
        MonsterCard *m = dynamic_cast<MonsterCard *>(zone->m_pCard);
        if (!zone->isEmpty() && m->getCardType() == CardType::MONSTER_CARD && m->getMonsterType() == MonsterType::SPELLCASTER)
            return true;
        else 
            return false;
    }
}

bool EffectRequirement::invigorationReq(){
    std::vector<Zone *>monsters = GameExternVars::pCurrentPlayer->field.monsterZone.m_monsterZone;

    for (Zone *zone : monsters)
    {
        if (zone->isEmpty())
            continue;
        
        MonsterCard *m = dynamic_cast<MonsterCard *>(zone->m_pCard);
        if (!zone->isEmpty() && m->getCardType() == CardType::MONSTER_CARD && m->getAttribute() == MonsterAttribute::EARTH)
            return true;
        else 
            return false;
    }
}

bool EffectRequirement::swordOfDarkDestructionReq(){
    std::vector<Zone *>monsters = GameExternVars::pCurrentPlayer->field.monsterZone.m_monsterZone;

    for (Zone *zone : monsters)
    {
        if (zone->isEmpty())
            continue;
        
        MonsterCard *m = dynamic_cast<MonsterCard *>(zone->m_pCard);
        if (!zone->isEmpty() && m->getCardType() == CardType::MONSTER_CARD && m->getAttribute() == MonsterAttribute::DARK)
            return true;
        else 
            return false;
    }
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
