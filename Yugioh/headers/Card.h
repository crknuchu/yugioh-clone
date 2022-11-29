#ifndef CARD_H
#define CARD_H

#include <string>
#include <vector>
#include <QGraphicsPixmapItem>
#include <QGraphicsItem>
#include <QGraphicsSceneHoverEvent>


enum class CardType
{
    MONSTER_CARD,
    SPELL_CARD,
    TRAP_CARD
};

enum class CardLocation
{
    HAND,
    DECK,
    GRAVEYARD,
    FIELD
};

class Card:public QGraphicsPixmapItem
{
public:

    virtual ~Card();

    const std::string &getCardName() const;

    std::string getCardTypeString() const;

    CardType getCardType() const;


    CardLocation getCardLocation() const;

    std::string  getCardLocationString() const;

    void setCardLocation(CardLocation newCardLocation);

    const std::string &getCardDescription() const;

    //virtual void placeCardOnField();

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
    // Constructor is protected in order to restrict call to it to Card's child classes.
    Card(const std::string &cardName, CardType cardType, CardLocation cardLocation, const std::string &cardDescription, QGraphicsItem *parent = 0);
    std::string cardName;
    CardType cardType;
    CardLocation cardLocation;
    std::string cardDescription;
    //cardImage
    CardMenu *cardMenu = new CardMenu(this);



private:
//    std::string cardName = "";
    // TODO: Remove this
    std::string owner = "";
    float height;
    float width;

};

std::ostream &operator<<(std::ostream &out, Card &c);

#endif // CARD_H
