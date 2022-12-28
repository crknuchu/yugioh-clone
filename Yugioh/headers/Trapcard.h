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

    TrapCard(TrapType type, const std::string &cardName, CardType cardType, CardLocation cardLocation, SpellTrapPosition position, const std::string &cardDescription,std::string imagePath,bool active = false,bool setThisTurn = false);


    TrapType getTrapType() const;
    std::string getTrapTypeString() const;
    SpellTrapPosition getTrapPosition() const;
    void activateTrap();
    void setCardMenu() override;
    void setPosition(SpellTrapPosition newPosition);

    bool getActive() const;

protected:
    TrapType trapType;
    bool setThisTurn;
    bool active;
    SpellTrapPosition position;
};

#endif // TRAPCARD_H
