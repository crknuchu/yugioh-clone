#include "headers/Card.h"
#include <QPixmap>
#include <QSize>
#include <QDebug>
#include <iostream>
#include <QGraphicsSceneMouseEvent>

Card::Card(QGraphicsItem *parent){
    //set graphics
    QPixmap pixmap(":/resources/blue_eyes.jpg");
    pixmap = pixmap.scaled(QSize(200,150),Qt::KeepAspectRatio); //pixmap size needs to not be hardcoded
    height = pixmap.height();
    width = pixmap.width();
    setPixmap(pixmap);
    setAcceptHoverEvents(true);
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
