#include "headers/Card.h"
#include<numeric>
#include<iterator>
#include <iostream>


Card::Card(const std::string &CardName, CardType CType, CardPlace CPlace, const std::string &CardDescription,QGraphicsItem *parent)
    :CardName(CardName)
    ,CType(CType)
    ,CPlace(CPlace)
    ,CardDescription(CardDescription)
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
    return CardName;
}

std::string Card::getCType() const
{
    switch (CType) {
    case CardType::MonsterCard:
        return "MonsterCard";
    case CardType::TrapCard :
        return "TrapCard";
    default:
        return "SpellCard";
    }
}

CardPlace Card::getCPlace() const
{
    return CPlace;
}

void Card::setCPlace(CardPlace newCPlace)
{
    CPlace = newCPlace;
}

const std::string &Card::getCardDescription() const
{
    return CardDescription;
}

void Card::setCard()
{

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
    return out << "Card name: " << c.getCardName() << ", card type: " << c.getCType()  << std::endl;
}
