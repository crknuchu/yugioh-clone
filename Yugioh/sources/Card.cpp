#include "headers/Card.h"
#include <numeric>
#include <iterator>
#include <iostream>
#include "headers/CardMenu.h"
Card::Card(const std::string &cardName, CardType cardType, CardLocation cardLocation, const std::string &cardDescription,std::string imagePath)
    :cardName(cardName)
    ,cardType(cardType)
    ,cardLocation(cardLocation)
    ,cardDescription(cardDescription)
    ,imagePath(imagePath)
{
    QPixmap pixmap;
    pixmap.load(QString::fromStdString(imagePath));
    pixmap = pixmap.scaled(QSize(200,150), Qt::KeepAspectRatio); //pixmap size needs to not be hardcoded
    height = pixmap.height();
    width = pixmap.width();
    setPixmap(pixmap);
    setAcceptHoverEvents(true);
    this->setZValue(-9);
}

Card::~Card()
{
}

void Card::addToScene(QGraphicsScene *scene)
{
    scene->addItem(this);
    scene->addWidget(cardMenu);
}

void Card::flipCard()
{
    if(faceUp == true){
        QPixmap pixmap;
        pixmap.load(QString::fromStdString(":/resources/pictures/card_back.jpg"));
        pixmap = pixmap.scaled(QSize(200,150), Qt::KeepAspectRatio);
        setPixmap(pixmap);
        faceUp = false;
    }
    else{
        QPixmap pixmap;
        pixmap.load(QString::fromStdString(imagePath));
        pixmap = pixmap.scaled(QSize(200,150), Qt::KeepAspectRatio);
        setPixmap(pixmap);
        faceUp = true;
    }
    
}

const std::map<MonsterPosition, QString> Card::monsterPositionEnumToQString{
    {MonsterPosition::ATTACK,              "ATTACK"},
    {MonsterPosition::FACE_UP_DEFENSE,     "FACE_UP_DEFENSE"},
    {MonsterPosition::FACE_DOWN_DEFENSE,   "FACE_DOWN_DEFENSE"},
    {MonsterPosition::NONE,                "NONE"}
};

const std::map<SpellTrapPosition, QString> Card::spellTrapPositionEnumToQString{
    {SpellTrapPosition::FACE_UP,             "FACE_UP"},
    {SpellTrapPosition::SET,                 "SET"},
    {SpellTrapPosition::NONE,                "NONE"}
};

const std::map<QString, MonsterPosition> Card::monsterPositionQStringToEnum{
    {"ATTACK",              MonsterPosition::ATTACK},
    {"FACE_UP_DEFENSE",     MonsterPosition::FACE_UP_DEFENSE},
    {"FACE_DOWN_DEFENSE",   MonsterPosition::FACE_DOWN_DEFENSE},
    {"NONE",                MonsterPosition::NONE}
};

const std::map<QString, SpellTrapPosition> Card::spellTrapPositionQStringToEnum{
    {"FACE_UP",     SpellTrapPosition::FACE_UP},
    {"SET",         SpellTrapPosition::SET},
    {"NONE",        SpellTrapPosition::NONE}
};


const std::string &Card::getCardName() const
{
    return cardName;
}

CardType Card::getCardType() const
{
    return cardType;
}

std::string Card::getCardLocationString() const
{
    switch (cardLocation) {
    case CardLocation::HAND:
        return "hand";
    case CardLocation::DECK :
        return "deck";
    case CardLocation::GRAVEYARD:
        return "graveyard";
    case CardLocation::FIELD:
        return "field";
    default:
        return "error:unsupported card location";
    }
}

bool Card::getIsActivated() const
{
    return this->isActivated;
}

int Card::getPlayerThatSetThisCard() const
{
    return playerThatSetThisCard;
}

bool Card::getIsSetThisTurn() const
{
    return this->isSetThisTurn;
}


CardLocation Card::getCardLocation() const
{
    return cardLocation;
}

std::string Card::getCardTypeString() const
{
    switch (cardType) {
    case CardType::MONSTER_CARD:
        return "monster card";
    case CardType::TRAP_CARD :
        return "trap card";
    case CardType::SPELL_CARD :
        return "spell card";
    default:
        return "error: unsupported card type";
    }
}


void Card::setCardLocation(CardLocation newCardLocation)
{
    cardLocation = newCardLocation;
}

void Card::setIsActivated(bool isActivated)
{
    this->isActivated = isActivated;
}

void Card::setPlayerThatSetThisCard(int playerNumber)
{
    this->playerThatSetThisCard = playerNumber;
}

void Card::setIsSetThisTurn(bool isSetThisTurn)
{
    this->isSetThisTurn = isSetThisTurn;
}

const std::string &Card::getCardDescription() const
{
    return cardDescription;
}



bool Card::operator==(const Card &other) const
{
    return this->getCardName() == other.getCardName();
}

void Card::hoverEnterEvent(QGraphicsSceneHoverEvent *event){
    // TODO: Is this even possible since QGraphicsPixmapItem doesn't inherit QObject
    emit cardHoveredEnter(*this);
}

void Card::hoverLeaveEvent(QGraphicsSceneHoverEvent *event){
    emit cardHoveredLeave(*this);
}

void Card::hoverMoveEvent(QGraphicsSceneHoverEvent *event){

}

void Card::mousePressEvent(QGraphicsSceneMouseEvent *event){
    std::cout << "Card " << this->getCardName() << " was clicked!" << std::endl;
    if(event->buttons() & Qt::LeftButton)
    {
       emit cardSelected(this);
    }
}

void Card::move(float x,float y){
    setPos(x,y); //we need to implement a unified move() function that moves the card and the menu at the same time
    cardMenu->move(pos().x(),pos().y()-cardMenu->height());
    cardMenu->hide();
}

void Card::setName(std::string name){
    cardName = name;
}

float Card::getHeight(){
    return height;
}

float Card::getWidth(){
    return width;
}

std::ostream &operator<<(std::ostream &out, Card &c){
    return out << "Card name: " << c.getCardName() << ", card type: " << c.getCardTypeString()
               << ",card location: " << c.getCardLocationString() << ",card description: "<< c.getCardDescription() << std::endl;
}
