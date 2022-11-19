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

    TrapCard(TrapType type, const std::string &cardName, CardType cardType, CardLocation cardLocation, const std::string &cardDescription);
    virtual void setCard();
    TrapType getType() const;

protected:
    TrapType type;
};

#endif // TRAPCARD_H
