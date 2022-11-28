#ifndef TRAPCARD_H
#define TRAPCARD_H

#include "headers/Card.h"

enum class TrapType
{
    NORMAL_TRAP,
    CONTINUOUS_TRAP,
    COUNTER_TRAP,
};

class TrapCard : public Card
{
public:

    TrapCard(TrapType type, const std::string &cardName, CardType cardType, CardLocation cardLocation, const std::string &cardDescription,bool active = false);


    TrapType getTrapType() const;
    std::string getTrapTypeString() const;

    void activateTrap();

protected:
    TrapType trapType;
    bool active;
};

#endif // TRAPCARD_H
