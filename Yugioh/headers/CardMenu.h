#ifndef CARDMENU_H
#define CARDMENU_H

#include <QWidget>
#include <QPushButton>
#include <QVBoxLayout>
#include <QGraphicsSceneHoverEvent>
#include <QEvent>
#include <QMap>
#include <QString>

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

    void update(QMap<QString,bool> flags);

    bool visible = false;

protected:
   


private:

};


#endif // CARDMENU_H
