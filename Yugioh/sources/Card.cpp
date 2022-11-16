#include "headers/Card.h"
#include <QPixmap>
#include <QSize>
#include <QDebug>
#include <iostream>
#include <QGraphicsSceneMouseEvent>

Card::Card(QGraphicsItem *parent){
    //set graphics
    QPixmap pixmap(":/resources/card_back.jpg");
    
    pixmap = pixmap.scaled(QSize(200,150),Qt::KeepAspectRatio); //pixmap size needs to not be hardcoded
    height = pixmap.height();
    width = pixmap.width();
    setPixmap(pixmap);
}

void Card::mousePressEvent(QGraphicsSceneMouseEvent *event){
    pickCard();
    //TODO: implement menu that pops up from card with options for player to pick
}

void Card::pickCard(){
    std::cout<<cardName<<std::endl;
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
