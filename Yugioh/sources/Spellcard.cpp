#include "headers/Spellcard.h"

SpellCard::SpellCard(SpellType type, const std::string &cardName, CardType cardType, CardLocation cardLocation, SpellTrapPosition position, const std::string &cardDescription,bool active)
    : Card(cardName, cardType, cardLocation, cardDescription)
    ,type(type)
    ,active(active)
    ,position(position)
{}

SpellType SpellCard::getSpellType() const
{
    return type;
}

std::string SpellCard::getSpellTypeString() const
{
        switch (type) {
        case SpellType::NORMAL_SPELL:
            return "normal spell";
        case SpellType::CONTINUOUS_SPELL :
            return "constinious spell";
        case SpellType::EQUIP_SPELL:
            return "equip spell";
        case SpellType::QUICK_SPELL:
            return "quick spell";
        case SpellType::FIELD_SPELL:
            return "field spell";
        case SpellType::RITUAL_SPELL:
            return "ritual spell";
        default:
            return "error:unknown spell type";
        }
}

SpellTrapPosition SpellCard::getSpellPosition() const
{
    return position;
}

void SpellCard::activateSpell()
{
    this->active = true;
}

void SpellCard::setCardMenu(){
    QMap<QString, bool> flagMap ;
    if(cardLocation == CardLocation::HAND && (GamePhaseExternVars::currentGamePhase == GamePhases::MAIN_PHASE1 || GamePhaseExternVars::currentGamePhase == GamePhases::MAIN_PHASE2)){
        flagMap.insert("set",true);
        flagMap.insert("activate",true);
    }
     if(cardLocation == CardLocation::FIELD){
         flagMap.insert("activate",true);
        }
     cardMenu->update(flagMap);
};
