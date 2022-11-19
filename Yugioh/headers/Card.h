#ifndef CARD_H
#define CARD_H

#include <string>
#include <vector>
#include <QGraphicsPixmapItem>
#include <QGraphicsItem>
#include <QGraphicsSceneHoverEvent>


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

class Card:public QGraphicsPixmapItem
{
public:

    Card(const std::string &CardName, CardType CType, CardPlace CPlace, const std::string &CardDescription,QGraphicsItem *parent = 0);

    virtual ~Card();

    const std::string &getCardName() const;

    std::string getCType() const;

    CardPlace getCPlace() const;
    void setCPlace(CardPlace newCPlace);

    const std::string &getCardDescription() const;

    virtual void setCard();

    bool operator==(const Card &card) const;

    void menuPopUp(QGraphicsSceneHoverEvent *event);
    void mousePressEvent(QGraphicsSceneMouseEvent*event);
    void setName(std::string name);
    float getHeight();
    float getWidth();
    void hoverEnterEvent(QGraphicsSceneHoverEvent *event);
    void hoverLeaveEvent(QGraphicsSceneHoverEvent *event);
    void hoverMoveEvent(QGraphicsSceneHoverEvent *event);


protected:
    std::string CardName;
    CardType CType;
    CardPlace CPlace;
    std::string CardDescription;
    //CardImage



private:
    std::string cardName = "";
    std::string owner = "";
    float height;
    float width;

};

std::ostream &operator<<(std::ostream &out, Card &c);

#endif // CARD_H
