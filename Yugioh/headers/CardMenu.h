#ifndef CARDMENU_H
#define CARDMENU_H

#include <QWidget>
#include <QPushButton>
#include <QVBoxLayout>
#include <QGraphicsSceneHoverEvent>
#include <QEvent>
#include <QMap>
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

    void update(QMap<QString,bool>flagmap);

    bool visible = false;

protected:
   


private:

};


#endif // CARDMENU_H
