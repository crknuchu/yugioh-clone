#include "headers/Card.h"
#include<numeric>
#include<iterator>
#include <iostream>


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
    cardMenu->hide();
}

Card::~Card()
{
}

const std::string &Card::getCardName() const
{
    return cardName;
}

std::string Card::getCardType() const
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

CardLocation Card::getCardLocation() const
{
    return cardLocation;
}

void Card::setCardLocation(CardLocation newCardLocation)
{
    cardLocation = newCardLocation;
}

const std::string &Card::getCardDescription() const
{
    return cardDescription;
}

void Card::setCard()
{

}

bool Card::operator==(const Card &other) const
{
    return this->getCardName() == other.getCardName();
}

void Card::hoverEnterEvent(QGraphicsSceneHoverEvent *event){

}

void Card::hoverLeaveEvent(QGraphicsSceneHoverEvent *event){
    std::cout<<"leave"<<std::endl;
}

void Card::hoverMoveEvent(QGraphicsSceneHoverEvent *event){

}

void Card::mousePressEvent(QGraphicsSceneMouseEvent *event){
    if(cardMenu->visible == false){
        cardMenu->show();
        cardMenu->visible = true;
    }
    else{
        cardMenu->hide();
        cardMenu->visible = false;
    }
}

void Card::move(float x,float y){
    setPos(x,y); //we need to implement a unified move() function that moves the card and the menu at the same time
    cardMenu->move(pos().x(),pos().y()-cardMenu->height());
}

// void Card::menuPopUp(QGraphicsSceneHoverEvent *event){
//     // std::cout<<"menu pops up"<<std::endl;
//     cardMenu->show();
// }

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
    return out << "Card name: " << c.getCardName() << ", card type: " << c.getCardType()  << std::endl;
}
