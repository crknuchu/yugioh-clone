#ifndef SERIALIZER_H
#define SERIALIZER_H

#include <QString>
#include <QFile>
#include <QDebug>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonValue>
#include <QJsonArray>

#include "headers/Card.h"
#include "headers/Monstercard.h"
#include "headers/Trapcard.h"
#include "headers/Spellcard.h"

#include <map>
#include <vector>

class Serializer //change name to JsonSerializer
{
public:
    Serializer();

    void loadFromJson(QString s);


    std::vector<Card*> getCards();

private:
    std::vector<Card*> arrayOfCards;
};

namespace Maps{
    extern std::map<QString,MonsterAttribute> stringToMonsterAttribute;
    extern std::map<QString,MonsterType> stringToMonsterType;
    extern std::map<QString,MonsterKind> stringToMonsterKind;
    extern std::map<QString,SpellType> stringToSpellType;
    extern std::map<QString,TrapType> stringToTrapType;
}

#endif // SERIALIZER_H
