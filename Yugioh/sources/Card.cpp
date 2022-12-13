#include "headers/Card.h"
#include <numeric>
#include <iterator>
#include <iostream>
#include "headers/CardMenu.h"
Card::Card(const std::string &cardName, CardType cardType, CardLocation cardLocation, const std::string &cardDescription, QGraphicsPixmapItem *parent)
    : QGraphicsPixmapItem(parent)
    ,cardName(cardName)
    ,cardType(cardType)
    ,cardLocation(cardLocation)
    ,cardDescription(cardDescription)
{
    QPixmap pixmap(":/resources/blue_eyes.jpg");
    pixmap = pixmap.scaled(QSize(200,150), Qt::KeepAspectRatio); //pixmap size needs to not be hardcoded
    height = pixmap.height();
    width = pixmap.width();
    setPixmap(pixmap);
    setAcceptHoverEvents(true);
}

Card::~Card()
{
}

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
        return "fiels";
    default:
        return "error:unsupported card location";
    }
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
    if(event->buttons() & Qt::LeftButton)
    {
       emit cardSelected(this);
    }
}

void Card::move(float x,float y){
    setPos(x,y); //we need to implement a unified move() function that moves the card and the menu at the same time
    cardMenu->move(pos().x(),pos().y()-cardMenu->height());
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
