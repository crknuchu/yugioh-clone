#ifndef CARDMENU_H
#define CARDMENU_H

#include <QWidget>
#include <QPushButton>
#include <QVBoxLayout>
// #include "headers/Card.h"

class CardMenu: public QWidget
{
public:
    CardMenu();
    CardMenu(int x,int y);
    QPushButton *activateButton = new QPushButton("Activate");
    QPushButton *setButton = new QPushButton("Set");
    QVBoxLayout *layout = new QVBoxLayout(this);

    void setWidth(int width);



protected:
   


private:

};


#endif // CARDMENU_H
