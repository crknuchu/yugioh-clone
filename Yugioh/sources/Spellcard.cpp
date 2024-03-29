#include "headers/Spellcard.h"
#include "headers/EffectRequirement.h"

SpellCard::SpellCard(SpellType type, const std::string &cardName, CardType cardType, CardLocation cardLocation, SpellTrapPosition position,
                     const std::string &cardDescription, std::string imagePath, bool active)
    : Card(cardName, cardType, cardLocation, cardDescription, imagePath)
    ,type(type)
    ,active(active)
    ,position(position)
{}

SpellCard* SpellCard::clone() {
    return new SpellCard(this->type, this->cardName, this->cardType, this->cardLocation, this->position,
                         this->cardDescription, this->imagePath, this->active);
}

bool SpellCard::shouldBeSentToGraveyard()
{
    if(type == SpellType::CONTINUOUS_SPELL)
        return false;

    if(type == SpellType::EQUIP_SPELL)
        return false;

    if(type == SpellType::FIELD_SPELL)
        return false;

    return true;
}

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

void SpellCard::setCardMenu(bool isMonsterZoneFull,bool OpponentHaveMonsters){

    QMap<QString, bool> flagMap {{"set",false},{"summon",false},{"reposition",false},{"activate",false},{"attack",false}};
    EffectRequirement effectRequirement(*this);
    bool cardActivationRequirement = effectRequirement.isActivatable(this->cardName);

    if(cardLocation == CardLocation::HAND && (GamePhaseExternVars::currentGamePhase == GamePhases::MAIN_PHASE1 ||
                                              GamePhaseExternVars::currentGamePhase == GamePhases::MAIN_PHASE2)){
        flagMap.insert("set",true);
        if(cardActivationRequirement)
            flagMap.insert("activate",true);
    }
     if(cardLocation == CardLocation::FIELD && cardActivationRequirement){
         flagMap.insert("activate",true);
        }
     cardMenu->update(flagMap);
}

void SpellCard::setPosition(SpellTrapPosition newPosition)
{
    position = newPosition;
}

bool SpellCard::getActive() const
{
    return active;
};
