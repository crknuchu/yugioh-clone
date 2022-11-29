#ifndef CARDMENU_H
#define CARDMENU_H

#include <QWidget>
#include <QPushButton>
#include <QVBoxLayout>

class CardMenu: public QWidget
{
public:
    CardMenu();
    // CardMenu(Card *parent);
    QPushButton *activateButton = new QPushButton("Activate");
    QPushButton *setButton = new QPushButton("Set");
    QVBoxLayout *layout = new QVBoxLayout(this);



protected:
   


private:

};


#endif // CARDMENU_H
