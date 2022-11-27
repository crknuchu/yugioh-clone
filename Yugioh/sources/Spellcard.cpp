#include "headers/Spellcard.h"
#include "headers/Card.h"


SpellCard::SpellCard(SpellType type, const std::string &cardName, CardType cardType, CardLocation cardLocation, const std::string &cardDescription)
    : Card(cardName, cardType, cardLocation, cardDescription)
    ,type(type)
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




