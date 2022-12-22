#include "headers/Spellcard.h"

SpellCard::SpellCard(SpellType type, const std::string &cardName, CardType cardType, CardLocation cardLocation, const std::string &cardDescription,std::string imagePath,bool active)
    : Card(cardName, cardType, cardLocation, cardDescription,imagePath)
    ,type(type)
    ,active(active)
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

void SpellCard::activateSpell()
{
    this->active = true;
}

void SpellCard::setCardMenu(){

    QMap<QString, bool> flagMap {{"set",false},{"summon",false},{"reposition",false},{"activate",false},{"attack",false}};

    if(cardLocation == CardLocation::HAND && (GamePhase::currentGamePhase == GamePhasesEnum::MAIN_PHASE1 || GamePhase::currentGamePhase == GamePhasesEnum::MAIN_PHASE2)){
        flagMap.insert("set",true);
        flagMap.insert("activate",true);
    }
     if(cardLocation == CardLocation::FIELD){
         flagMap.insert("activate",true);
        }
     cardMenu->update(flagMap);
};
