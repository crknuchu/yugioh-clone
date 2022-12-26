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

    void update(QMap<QString,bool> flags);
    void setUpLayout();

    QPushButton *activateButton = new QPushButton("Activate");
    QPushButton *setButton = new QPushButton("Set");
    QPushButton *summonButton = new QPushButton("Summon");
    QPushButton *repositionButton = new QPushButton("Reposition");
    QPushButton *attackButton = new QPushButton("Attack");
    QPushButton *attackDirectlyButton = new QPushButton("Atk Direct");
    QVBoxLayout *layout = new QVBoxLayout(this);

protected:

private:

};


#endif // CARDMENU_H
