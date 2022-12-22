#include "headers/Serializer.h"
#include <iostream>

Serializer::Serializer()
{

}

Serializer::Serializer(QString s)
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
        // qWarning() << item.toObject()["name"].toString();
        CardType cardType;
        if(item.toObject()["type"].toString() == "Normal Monster")
           cardType = CardType::MONSTER_CARD;
        else if(item.toObject()["type"].toString() == "Spell Card")
            cardType = CardType::SPELL_CARD;
        else
            cardType = CardType::TRAP_CARD;
        std::string name = item.toObject()["name"].toString().toStdString();
        QString desc = item.toObject()["desc"].toString();
        int atk = item.toObject()["atk"].toInt();
        int def = item.toObject()["def"].toInt();
        int level = item.toObject()["level"].toInt();
        MonsterKind race = Maps::stringToMonsterKind[item.toObject()["race"].toString()]; //kind
        MonsterAttribute attribute = Maps::stringToMonsterAttribute[item.toObject()["attribute"].toString()];
        MonsterType type = Maps::stringToMonsterType[item.toObject()["archetype"].toString()];

        MonsterCard *c = new MonsterCard("test",atk,def,level,type,race,attribute,false,Position::NONE,false,cardType,CardLocation::DECK,"test",false);
        qWarning()<< c->getAttackPoints();
    }
}

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

