#include "profilesettings.h"
#include "ui_profilesettings.h"
#include "QPixmap"
#include "QGraphicsPixmapItem"
#include "QGraphicsItem"
#include "QGraphicsView"
#include <iostream>
avatars currentAvatar;
sleeves currentSleeve;

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
    QPixmap imageBackG(":/resources/pictures/space.jpeg");
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
    ui->sleeveWindow->setStyleSheet("border: 5px solid grey");
    currentSleeve = sleeves::GREEN;


    scene = new QGraphicsScene(this);
    ui->sleeveWindow->setScene(scene);
    ui->sleeveWindow->setBackgroundBrush(b);

    QPixmap avatar(":/resources/pictures/yugi.png");
    currentAvatar = avatars::YUGI;

    ui->avatarWindow->setStyleSheet("border: 3px solid grey");
    ui->avatarWindow->setPixmap(avatar);
    ui->avatarWindow->setMaximumHeight(200);
    ui->avatarWindow->setScaledContents(true);
    ui->avatarWindow->setMaximumWidth(200);
}

void profileSettings::setUpConnections(){
    connect(ui->nextAvatar, &QPushButton::clicked, this, &profileSettings::changeAvatar);
    connect(ui->lastAvatar, &QPushButton::clicked, this, &profileSettings::changeAvatar);

    connect(ui->nextSleeve, &QPushButton::clicked, this, &profileSettings::changeSleeveNext);
    connect(ui->lastSleeve, &QPushButton::clicked, this, &profileSettings::changeSleevePrevious);

    connect(ui->save, &QPushButton::clicked, this, &profileSettings::saveChanges);
    connect(ui->cancel, &QPushButton::clicked, this, &profileSettings::undoChanges);
}


profileSettings::~profileSettings()
{
    delete ui;
}

void profileSettings::changeAvatar(){

    switch(currentAvatar){
        case(avatars::KAIBA):{
            QPixmap pic1(":/resources/pictures/kaiba.png");
            ui->avatarWindow->clear();
            ui->avatarWindow->setPixmap(pic1);
            currentAvatar = avatars::YUGI;
            std::cout<<"YUGI"<<std::endl;
        break;
           }
        case(avatars::YUGI):{
                QPixmap pic(":/resources/pictures/yugi.png");
                ui->avatarWindow->clear();
                ui->avatarWindow->setPixmap(pic);
                currentAvatar = avatars::KAIBA;
                std::cout<<"KAIBA"<<std::endl;
                break;
        }
    }

}


void profileSettings::changeSleeveNext(){
    switch(currentSleeve){
        case(sleeves::BLACK):{
            ui->sleeveWindow->setBackgroundBrush(QBrush(Qt::black));
            currentSleeve = sleeves::RED;
            break;
     }
        case(sleeves::RED):{
            ui->sleeveWindow->setBackgroundBrush(QBrush(Qt::red));
            currentSleeve = sleeves::WHITE;
            break;
     }
        case(sleeves::WHITE):{
            ui->sleeveWindow->setBackgroundBrush(QBrush(Qt::white));
            currentSleeve = sleeves::GREEN;
            break;
     }
        case(sleeves::GREEN):{
            ui->sleeveWindow->setBackgroundBrush(QBrush(Qt::green));
            currentSleeve = sleeves::BLUE;
            break;
     }
        case(sleeves::BLUE):{
            ui->sleeveWindow->setBackgroundBrush(QBrush(Qt::blue));
            currentSleeve = sleeves::BLACK;
            break;
     }
    }
}

void profileSettings::changeSleevePrevious(){
    switch(currentSleeve){
        case(sleeves::BLACK):{
            ui->sleeveWindow->setBackgroundBrush(QBrush(Qt::black));
            currentSleeve = sleeves::BLUE;
            break;
     }
        case(sleeves::RED):{
            ui->sleeveWindow->setBackgroundBrush(QBrush(Qt::red));
            currentSleeve = sleeves::BLACK;
            break;
     }
        case(sleeves::WHITE):{
            ui->sleeveWindow->setBackgroundBrush(QBrush(Qt::white));
            currentSleeve = sleeves::RED;
            break;
     }
        case(sleeves::GREEN):{
            ui->sleeveWindow->setBackgroundBrush(QBrush(Qt::green));
            currentSleeve = sleeves::WHITE;
            break;
     }
        case(sleeves::BLUE):{
            ui->sleeveWindow->setBackgroundBrush(QBrush(Qt::blue));
            currentSleeve = sleeves::GREEN;
            break;
     }
    }
}



void profileSettings::saveChanges(){
    switch(currentAvatar){
        case(avatars::YUGI):{
            std::cout<<"YUGI"<<std::endl;
            break;
        }
        case(avatars::KAIBA)
        :{
            std::cout<<"KAIBA"<<std::endl;
        }

    }

    close();
}

void profileSettings::undoChanges(){
    currentAvatar = avatars::YUGI;
    currentSleeve = sleeves::BLACK;
    close();
}
