#ifndef CARDMENU_H
#define CARDMENU_H

#include <QWidget>
#include <QPushButton>
#include <QVBoxLayout>
#include <QGraphicsSceneHoverEvent>
#include <QEvent>
// #include "headers/Card.h"

class CardMenu: public QWidget
{
public:
    CardMenu();
    CardMenu(int x,int y);
    QPushButton *activateButton = new QPushButton("Activate");
    QPushButton *setButton = new QPushButton("Set");
    QVBoxLayout *layout = new QVBoxLayout(this);

    void leaveEvent(QEvent *event);

    void setWidth(int width);

    bool visible = false;

protected:
   
};


#endif // CARDMENU_H
