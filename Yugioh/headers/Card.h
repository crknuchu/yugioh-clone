#ifndef CARD_H
#define CARD_H

#include "CardMenu.h"
#include "GamePhase.h"

#include <string>
#include <vector>
#include <QGraphicsPixmapItem>
#include <QGraphicsItem>
#include <QGraphicsSceneHoverEvent>
#include <QEvent>
#include <QMouseEvent>
#include <QGraphicsSceneMouseEvent>
#include <QMap>
#include <QString>
#include <QGraphicsScene>

class Game;

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
    FIELD,
    ATTACK,
    DEFENSE,
    SPELL_TRAP_ZONE
};

enum class MonsterPosition{
    ATTACK,
    FACE_UP_DEFENSE,
    FACE_DOWN_DEFENSE,
    NONE
};

enum class SpellTrapPosition{
    SET,
    FACE_UP,
    NONE
};


class Card : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:

    friend class Player;

    virtual ~Card();

    virtual Card* clone() = 0;

    virtual bool shouldBeSentToGraveyard() = 0;

    const std::string &getCardName() const;

    std::string getCardTypeString() const;

    CardType getCardType() const;

    CardLocation getCardLocation() const;

    std::string  getCardLocationString() const;

    bool getIsActivated() const;

    int getPlayerThatSetThisCard() const;

    bool getIsSetThisTurn() const;

    void setCardLocation(CardLocation newCardLocation);

    void setIsActivated(bool isActivated);

    void setPlayerThatSetThisCard(int playerNumber);

    void setIsSetThisTurn(bool isSetThisTurn);

    const std::string &getCardDescription() const;

    //virtual void placeCardOnField();

    virtual void setCardMenu(bool isMonsterZoneFull,bool OpponentHaveMonsters) = 0;

    bool operator==(const Card &card) const;

    void menuPopUp(QGraphicsSceneHoverEvent *event);
    void mousePressEvent(QGraphicsSceneMouseEvent*event);
    void setName(std::string name);
    float getHeight();
    float getWidth();
    void hoverEnterEvent(QGraphicsSceneHoverEvent *event);
    void hoverLeaveEvent(QGraphicsSceneHoverEvent *event);
    void hoverMoveEvent(QGraphicsSceneHoverEvent *event);
    void move(float x,float y);
    void flipCard();
    void addToScene(QGraphicsScene *scene);
    bool faceUp = true; //card is turned face up (image is visible) or facedown (back is visible)
    std::string imagePath;

    CardMenu *cardMenu = new CardMenu();
    float height;
    float width;//only for testing purposes

    static const std::map<MonsterPosition, QString> monsterPositionEnumToQString;
    static const std::map<SpellTrapPosition, QString> spellTrapPositionEnumToQString;

    static const std::map<QString, MonsterPosition> monsterPositionQStringToEnum;
    static const std::map<QString, SpellTrapPosition> spellTrapPositionQStringToEnum;



protected:
    // Constructor is protected in order to restrict call to it to Card's child classes.
    Card(const std::string &cardName, CardType cardType, CardLocation cardLocation, const std::string &cardDescription,std::string imagePath);
    std::string cardName;
    CardType cardType;
    CardLocation cardLocation;
    std::string cardDescription;
    bool isActivated = false;
    bool isSetThisTurn = false;
    int playerThatSetThisCard = 1;
    //cardImage
    // CardMenu *cardMenu = new CardMenu(this);
    
private:


signals:
   void cardHoveredEnter(Card &);
   void cardHoveredLeave(Card &);
   void cardSelected(Card *);

};

std::ostream &operator<<(std::ostream &out, Card &c);

#endif // CARD_H
