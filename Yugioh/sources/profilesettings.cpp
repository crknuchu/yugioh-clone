#include "profilesettings.h"
#include "ui_profilesettings.h"
#include "QPixmap"
#include "QGraphicsPixmapItem"
#include "QGraphicsItem"
#include "QGraphicsView"



profileSettings::profileSettings(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::profileSettings)
{
    ui->setupUi(this);


    setUpConnections();
    ui->sleeveWindow->setBaseSize(400, 500);
//    ui->sleeveWindow->setMaximumSize(300, 400);
    ui->cancel->setMaximumSize(50, 100);
    ui->save->setMaximumSize(50, 100);

    //background
    QPixmap imageBackG(":/resources/avatars.jpg");
    imageBackG = imageBackG.scaled(this->size(), Qt::KeepAspectRatioByExpanding);
    QBrush brush(imageBackG);
    QPalette palette;
    palette.setBrush(QPalette::Window, brush);
    this->setPalette(palette);

    //labels
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


    //sleeves
    QBrush b(Qt::green);
    ui->sleeveWindow->setBackgroundBrush(b);
//    ui->sleeveWindow->show();

//    cardSleve = ui->sleeveWindow;
//    cardSleve->setBackgroundBrush(b);

    scene = new QGraphicsScene(this);
    ui->sleeveWindow->setScene(scene);
    ui->sleeveWindow->setBackgroundBrush(b);
//    ui->sleeveWindow->fitInView(ui->sleeveWindow->sceneRect(), Qt::IgnoreAspectRatio);

    QImage avatar(":/resources/yugi.png");
//    card = card.scaled(ui->sleeveWindow->width(), ui->sleeveWindow->height());

    QBrush a(avatar);/*
    ui->avatarWindow->setBackgroundBrush(a);
    ui->avatarWindow->show();*/
    \
    ui->avatarWindow->setScene(scene);
    ui->avatarWindow->setBackgroundBrush(a);
    ui->avatarWindow->fitInView(ui->avatarWindow->sceneRect(), Qt::KeepAspectRatio);
}

void profileSettings::setUpConnections(){
    connect(ui->nextAvatar, &QPushButton::clicked, this, &profileSettings::changeAvatar);
    connect(ui->lastAvatar, &QPushButton::clicked, this, &profileSettings::changeAvatar);

    connect(ui->nextSleeve, &QPushButton::clicked, this, &profileSettings::changeSleeve);
    connect(ui->lastSleeve, &QPushButton::clicked, this, &profileSettings::changeSleeve);

    connect(ui->save, &QPushButton::clicked, this, &profileSettings::saveChanges);
    connect(ui->save, &QPushButton::clicked, this, &profileSettings::undoChanges);
}


profileSettings::~profileSettings()
{
    delete ui;
}

void profileSettings::changeAvatar(){
    QPixmap pic(":/resources/avatars.jpg");


    pic = pic.scaled(ui->avatarWindow->x()/100 - ui->avatarWindow->width(),
                     ui->avatarWindow->y()/100 - ui->avatarWindow->height(),
                     Qt::IgnoreAspectRatio);
    ui->avatarWindow->setBackgroundBrush(QBrush(pic));
}


void profileSettings::changeSleeve(){
    ui->sleeveWindow->setBackgroundBrush(QBrush(Qt::red));
}

void profileSettings::saveChanges(){}

void profileSettings::undoChanges(){}
