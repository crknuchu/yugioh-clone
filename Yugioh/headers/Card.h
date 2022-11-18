#ifndef CARD_H
#define CARD_H

#include <string>
#include <vector>


enum class CardType
{
    MonsterCard,
    SpellCard,
    TrapCard
};

enum class CardPlace
{
    Hand,
    Deck,
    Grave,
    Table
};

class Card
{
public:

    Card(const std::string &CardName, CardType CType, CardPlace CPlace, const std::string &CardDescription);

    virtual ~Card();

    const std::string &getCardName() const;

    std::string getCType() const;

    CardPlace getCPlace() const;
    void setCPlace(CardPlace newCPlace);

    const std::string &getCardDescription() const;

    virtual void setCard();


protected:
    std::string CardName;
    CardType CType;
    CardPlace CPlace;
    std::string CardDescription;
    //CardImage



private:

};

std::ostream &operator<<(std::ostream &out, Card &c);

#endif // CARD_H
