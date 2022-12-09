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

void TrapCard::setCardMenu(Game & game){
    if(cardLocation == CardLocation::HAND && (game.getGamePhase() == GamePhases::MAIN_PHASE1 || game.getGamePhase() == GamePhases::MAIN_PHASE2)){
        // set, activate = true
    }
    if(cardLocation == CardLocation::FIELD && setThisTurn == false){
        //flag activate = true
    }
        //call CardMenu(all flags from if)
};
