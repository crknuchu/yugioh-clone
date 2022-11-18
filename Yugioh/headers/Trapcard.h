#ifndef TRAPCARD_H
#define TRAPCARD_H

#include "headers/Card.h"


enum class TrapType
{
    NormalTrap,
    ContinuousTrap,
    CounterTraps,
    EquipTrap,
    FieldTrap,

};


class TrapCard : public Card
{
public:

    TrapCard(TrapType Ttype, const std::string &CardName, CardType CType, CardPlace CPlace, const std::string &CardDescription);
    virtual void setCard();
    TrapType getTtype() const;

protected:
    TrapType Ttype;
};

#endif // TRAPCARD_H
