#include "headers/Card.h"
#include<numeric>
#include<iterator>
#include <iostream>


Card::Card(const std::string &cardName, CardType cardType, CardLocation cardLocation, const std::string &cardDescription, QGraphicsItem *parent)
    :cardName(cardName)
    ,cardType(cardType)
    ,cardLocation(cardLocation)
    ,cardDescription(cardDescription)
{
    QPixmap pixmap(":/resources/blue_eyes.jpg");
    pixmap = pixmap.scaled(QSize(200,150),Qt::KeepAspectRatio); //pixmap size needs to not be hardcoded
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
        return "Hand";
    case CardLocation::DECK :
        return "Deck";
    case CardLocation::GRAVEYARD:
        return "Graveyard";
    default:
        return "Field";
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
        return "MonsterCard";
    case CardType::TRAP_CARD :
        return "TrapCard";
    default:
        return "SpellCard";
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

void Card::mousePressEvent(QGraphicsSceneMouseEvent *event){
    if(event->button() == Qt::LeftButton){
        // std::cout<<"left"<<std::endl;
    }
}

void Card::hoverEnterEvent(QGraphicsSceneHoverEvent *event){

    // if(event->type() == QEvent::HoverEnter){
    // std::cout<<"enter"<<std::endl;
    menuPopUp(event);
}

void Card::hoverLeaveEvent(QGraphicsSceneHoverEvent *event){
    std::cout<<"leave"<<std::endl;
}

void Card::hoverMoveEvent(QGraphicsSceneHoverEvent *event){
    //std::cout<<"move"<<std::endl;
}

void Card::menuPopUp(QGraphicsSceneHoverEvent *event){
    std::cout<<"menu pops up"<<std::endl;
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
