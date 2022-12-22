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

#include <map>

class Serializer:QObject
{
public:
    Serializer();
    Serializer(QString s);
    Card* getDeck();

};

namespace Maps{
    extern std::map<QString,MonsterAttribute> stringToMonsterAttribute;
    extern std::map<QString,MonsterType> stringToMonsterType;
    extern std::map<QString,MonsterKind> stringToMonsterKind;
}

#endif // SERIALIZER_H
