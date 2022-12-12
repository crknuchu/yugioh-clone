#include "headers/Trapcard.h"

TrapCard::TrapCard(TrapType type, const std::string &cardName, CardType cardType, CardLocation cardLocation, const std::string &cardDescription,bool active,bool setThisTurn)
    : Card(cardName, cardType, cardLocation, cardDescription)
    ,trapType(type)
    ,setThisTurn(setThisTurn)
    ,active(active)
{}


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
    QMap<QString, bool> flagMap ;
    if(cardLocation == CardLocation::HAND && (GamePhaseExternVars::currentGamePhase == GamePhases::MAIN_PHASE1 || GamePhaseExternVars::currentGamePhase == GamePhases::MAIN_PHASE2)){
        flagMap.insert("set",true);
        flagMap.insert("activate",true);
    }
    if(cardLocation == CardLocation::FIELD && setThisTurn == false){
        flagMap.insert("activate",true);
    }
    cardMenu->update(flagMap);
};
