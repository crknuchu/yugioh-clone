#include "profilesettings.h"
#include "ui_profilesettings.h"
#include "QPixmap"
#include "QGraphicsPixmapItem"
#include "QGraphicsItem"
#include "QGraphicsView"
#include <iostream>
avatars currentAvatar;

profileSettings::profileSettings(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::profileSettings)
{
    ui->setupUi(this);


    setUpConnections();
    ui->sleeveWindow->setBaseSize(400, 500);
    ui->cancel->setMaximumSize(50, 100);
    ui->save->setMaximumSize(50, 100);

    //background
    QPixmap imageBackG(":/resources/space.jpeg");
    imageBackG = imageBackG.scaled(this->size(), Qt::KeepAspectRatioByExpanding);
    QBrush brush(imageBackG);
    QPalette palette;
    palette.setBrush(QPalette::Window, brush);
    this->setPalette(palette);

    //labels
    QPalette textColor;
    textColor.setColor(QPalette::WindowText, Qt::white);
//    textColor.setColor(QPalette::Window, Qt::gray);

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


    scene = new QGraphicsScene(this);
    ui->sleeveWindow->setScene(scene);
    ui->sleeveWindow->setBackgroundBrush(b);

    QPixmap avatar(":/resources/yugi.png");
    currentAvatar = avatars::YUGI;

    ui->avatarWindow->setPixmap(avatar);
    ui->avatarWindow->setMaximumHeight(200);
    ui->avatarWindow->setScaledContents(true);
    ui->avatarWindow->setMaximumWidth(200);
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

    switch(currentAvatar){
        case(avatars::KAIBA):{
            QPixmap pic1(":/resources/kaiba.png");
            ui->avatarWindow->clear();
            ui->avatarWindow->setPixmap(pic1);
            currentAvatar = avatars::YUGI;
            std::cout<<"promena 1"<<std::endl;
        break;
           }
        case(avatars::YUGI):{
                QPixmap pic(":/resources/yugi.png");
                ui->avatarWindow->clear();
                ui->avatarWindow->setPixmap(pic);
                currentAvatar = avatars::KAIBA;
                std::cout<<"promena 2"<<std::endl;
                break;
        }
    }

}


void profileSettings::changeSleeve(){
    ui->sleeveWindow->setBackgroundBrush(QBrush(Qt::red));
}

void profileSettings::saveChanges(){}

void profileSettings::undoChanges(){}
