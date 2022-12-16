#include "profilesettings.h"
#include "ui_profilesettings.h"
#include "QPixmap"
#include "QGraphicsPixmapItem"
#include "QGraphicsItem"
profileSettings::profileSettings(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::profileSettings)
{
    ui->setupUi(this);
    ui->sleeveWindow->setBaseSize(300, 400);
    ui->sleeveWindow->setMaximumSize(300, 400);
    ui->cancel->setMaximumSize(50, 100);
    ui->save->setMaximumSize(50, 100);
//    scene = new QGraphicsScene();
    QPixmap imageBackG(":/resources/avatars.jpg");
    imageBackG = imageBackG.scaled(this->size(), Qt::KeepAspectRatioByExpanding);
    QBrush brush(imageBackG);
//    scene->addWidget(parent);
    QPalette palette;
    palette.setBrush(QPalette::Window, brush);
    this->setPalette(palette);

    QPalette textColor;
    textColor.setColor(QPalette::WindowText, Qt::white);
    textColor.setColor(QPalette::Window, Qt::gray);

    ui->lb1->setAutoFillBackground(true);
    ui->lb1->setPalette(textColor);

    ui->lb2->setAutoFillBackground(true);
    ui->lb2->setPalette(textColor);

    QFont font("Arial", 15, QFont::Bold);
    ui->lb1->setFont(font);
    ui->lb2->setFont(font);



//    ui->
}


profileSettings::~profileSettings()
{
    delete ui;
}
