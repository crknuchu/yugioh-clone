#ifndef CARDMENU_H
#define CARDMENU_H

#include <QWidget>
#include <QPushButton>
#include <QVBoxLayout>
#include <QGraphicsSceneHoverEvent>
#include <QEvent>

class CardMenu: public QWidget
{
public:
    CardMenu();

    QPushButton *activateButton = new QPushButton("Activate");
    QPushButton *setButton = new QPushButton("Set");
    QPushButton *summonButton = new QPushButton("Summon");
    QPushButton *repositionButton = new QPushButton("Reposition");
    QPushButton *attackButton = new QPushButton("Attack");
    QVBoxLayout *layout = new QVBoxLayout(this);

    bool visible = false;

protected:
   


private:

};


#endif // CARDMENU_H
