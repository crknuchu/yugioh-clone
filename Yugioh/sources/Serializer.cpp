#include "headers/Serializer.h"
#include <iostream>
Serializer::Serializer()
{

}

std::vector<Card*> Serializer::getCards()
{
    return arrayOfCards;
}

void Serializer::loadFromJson(QString s)
{
    QString val;
    QFile file;
    file.setFileName(s);
    file.open(QIODevice::ReadOnly | QIODevice::Text);
    val = file.readAll();
    file.close();
    QJsonDocument d = QJsonDocument::fromJson(val.toUtf8());
    QJsonObject obj = d.object();
    QJsonArray arr = obj["data"].toArray();

    for(auto item : arr){
        
        


        CardType cardType;
        if(item.toObject()["type"].toString() == "Normal Monster"){
            cardType = CardType::MONSTER_CARD;
            const std::string name = item.toObject()["name"].toString().toStdString();
            const std::string desc = item.toObject()["desc"].toString().toStdString();
            const std::string imagePath = item.toObject()["image"].toString().toStdString();
            int atk = item.toObject()["atk"].toInt();
            int def = item.toObject()["def"].toInt();
            int level = item.toObject()["level"].toInt();
            MonsterKind race = Maps::stringToMonsterKind[item.toObject()["race"].toString()]; //kind
            MonsterAttribute attribute = Maps::stringToMonsterAttribute[item.toObject()["attribute"].toString()];
            MonsterType type = Maps::stringToMonsterType[item.toObject()["archetype"].toString()];
            
            MonsterCard *monsterCard = new MonsterCard(name,atk,def,level,type,race,attribute,false,Position::NONE,false,cardType,CardLocation::DECK,desc,imagePath,false);
            arrayOfCards.push_back(monsterCard);
        }
        else if(item.toObject()["type"].toString() == "Spell Card"){

            cardType = CardType::SPELL_CARD;
            const std::string name = item.toObject()["name"].toString().toStdString();
            const std::string desc = item.toObject()["desc"].toString().toStdString();
            const std::string imagePath = item.toObject()["image"].toString().toStdString();
            SpellType spellType = Maps::stringToSpellType[item.toObject()["race"].toString()];
            SpellCard *spellCard = new SpellCard(spellType,name,cardType,CardLocation::DECK,desc,imagePath,false); 
            arrayOfCards.push_back(spellCard);
        }
        else{
            cardType = CardType::TRAP_CARD;
            const std::string name = item.toObject()["name"].toString().toStdString();
            const std::string desc = item.toObject()["desc"].toString().toStdString();
            const std::string imagePath = item.toObject()["image"].toString().toStdString();
            TrapType trapType = Maps::stringToTrapType[item.toObject()["race"].toString()];
        
            TrapCard *trapCard = new TrapCard(trapType,name,cardType,CardLocation::DECK,desc,imagePath,false,false);
            arrayOfCards.push_back(trapCard);
        }

    }
}

std::map<QString,TrapType> Maps::stringToTrapType{
    {"NORMAL TRAP",TrapType::NORMAL_TRAP},
    {"CONTINUOUS TRAP",TrapType::CONTINUOUS_TRAP},
    {"COUNTER_TRAP",TrapType::COUNTER_TRAP}
};

std::map<QString,SpellType> Maps::stringToSpellType{
    {"NORMAL SPELL",SpellType::NORMAL_SPELL},
    {"CONTINUOUS SPELL",SpellType::CONTINUOUS_SPELL},
    {"EQUIP SPELL",SpellType::EQUIP_SPELL},
    {"QUICK SPELL",SpellType::QUICK_SPELL},
    {"FIELD SPELL",SpellType::FIELD_SPELL},
    {"RITUAL SPELL",SpellType::RITUAL_SPELL}
};

std::map<QString,MonsterAttribute> Maps::stringToMonsterAttribute{
    {"DARK",MonsterAttribute::DARK},
    {"LIGHT",MonsterAttribute::LIGHT},
    {"DIVINE",MonsterAttribute::DIVINE},
    {"EARTH",MonsterAttribute::EARTH},
    {"FIRE",MonsterAttribute::FIRE},
    {"WATER",MonsterAttribute::WATER},
    {"WIND",MonsterAttribute::WIND}
};

std::map<QString,MonsterType> Maps::stringToMonsterType{
    {"AQUA",MonsterType::AQUA},
    {"BEAST",MonsterType::BEAST},
    {"BEAST WARRIOR",MonsterType::BEAST_WARRIOR},
    {"CREATOR GOD",MonsterType::CREATOR_GOD},
    {"DINOSAUR",MonsterType::DINOSAUR},
    {"DIVINE BEAST",MonsterType::DIVINE_BEAST},
    {"DRAGON",MonsterType::DRAGON},
    {"FAIRY",MonsterType::FAIRY},
    {"FIEND",MonsterType::FIEND},
    {"FISH",MonsterType::FISH},
    {"INSECT",MonsterType::INSECT},
    {"MACHINE",MonsterType::MACHINE},
    {"PLANT",MonsterType::PLANT},
    {"PSYCHIC",MonsterType::PSYCHIC},
    {"REPTILE",MonsterType::REPTILE},
    {"ROCK",MonsterType::ROCK},
    {"SPELL CASTER",MonsterType::SPELLCASTER},
    {"WARRIOR",MonsterType::WARRIOR},
    {"WINGED BEAST",MonsterType::WINGED_BEAST}
};

std::map<QString,MonsterKind> Maps::stringToMonsterKind{
    {"NORMAL MONSTER",MonsterKind::NORMAL_MONSTER},
    {"EFFECT MONSTER",MonsterKind::EFFECT_MONSTER},
    {"RITUAL MONSTER",MonsterKind::RITUAL_MONSTER},
};

