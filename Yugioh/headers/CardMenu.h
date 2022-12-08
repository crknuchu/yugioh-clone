#ifndef CARDMENU_H
#define CARDMENU_H

#include <QWidget>
#include <QPushButton>
#include <QVBoxLayout>
#include <QGraphicsSceneHoverEvent>
#include <QEvent>
//#include "headers/Card.h" // We have an include circle if this is uncommented

class CardMenu: public QWidget
{
public:
    CardMenu();
    CardMenu(int x,int y);
    QPushButton *activateButton = new QPushButton("Activate");
    QPushButton *setButton = new QPushButton("Set");
    QPushButton *summonButton = new QPushButton("Summon");
    QVBoxLayout *layout = new QVBoxLayout(this);

    void leaveEvent(QEvent *event);

    void setWidth(int width);

    bool visible = false;


// Pseudocode
// MyButton : QPushbutton
//{
//    signals:
//      void onClick(const Card*);
//}

protected:
   
};


#endif // CARDMENU_H
