#include "headers/Game.h"
#include <iostream>
#include <QGraphicsScene>
#include "headers/Card.h"

Game::Game() {
    // create a scene

    scene = new QGraphicsScene(this);

    scene->setSceneRect(0,0,800,600); //make the scene not hardcoded

    setScene(scene);

    setFixedSize(800,600);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setWindowTitle("Yu-Gi-Oh!");

    //creating items
    Card *c = new Card();
    c->setName("karta1");
    Card *c1 = new Card();
    c1->setName("karta2");

    //adding items
    scene->addItem(c);
    scene->addItem(c1);
    c->setPos(0, scene->height() - c->getHeight());
}