#include "headers/Trapcard.h"
#include "headers/EffectRequirement.h"

TrapCard::TrapCard(TrapType type, const std::string &cardName, CardType cardType, CardLocation cardLocation, const std::string &cardDescription,std::string imagePath,bool active,bool setThisTurn)
    : Card(cardName, cardType, cardLocation, cardDescription,imagePath)
    ,trapType(type)
    ,setThisTurn(setThisTurn)
    ,active(active)
{}

TrapCard* TrapCard::clone() {
    return new TrapCard(this->trapType, this->cardName, this->cardType, this->cardLocation,
                        this->cardDescription, this->imagePath, this->active, this->setThisTurn);
}

TrapType TrapCard::getTrapType() const
{
    return trapType;
}

std::string TrapCard::getTrapTypeString() const
{
    switch (trapType) {
    case TrapType::NORMAL_TRAP:
        return "normal trap";
    case TrapType::CONTINUOUS_TRAP :
        return "constinious trap";
    case TrapType::COUNTER_TRAP:
        return "counter trap";
    default:
        return "error:unknown trap type";
    }
}

void TrapCard::activateTrap()
{
    this->active = true;
}

void TrapCard::setCardMenu(){
    QMap<QString, bool> flagMap {{"set",false},{"summon",false},{"reposition",false},{"activate",false},{"attack",false}};
    EffectRequirement effectRequirement(*this);
    bool cardActivationRequirement = effectRequirement.isActivatable(this->cardName);
    if(cardLocation == CardLocation::HAND && (GamePhaseExternVars::currentGamePhase == GamePhases::MAIN_PHASE1 || GamePhaseExternVars::currentGamePhase == GamePhases::MAIN_PHASE2)){
        flagMap.insert("set",true);
        if(cardActivationRequirement)
            flagMap.insert("activate",true);
    }
    if(cardLocation == CardLocation::FIELD && setThisTurn == false && cardActivationRequirement){
        flagMap.insert("activate",true);
    }
    cardMenu->update(flagMap);
};
