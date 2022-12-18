#include "headers/GameSettings.h"
#include "ui_GameSettings.h"
#include <iostream>
GameSettings::GameSettings(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::GameSettings)
{
    ui->setupUi(this);

    QPixmap bkgnd(":/resources/pictures/background.jpg");
    bkgnd = bkgnd.scaled(this->size(), Qt::IgnoreAspectRatio);
    QPalette palette;
    palette.setBrush(QPalette::Window, bkgnd);
    this->setPalette(palette);

    ui->SetLifepoints->addItem("2000");
    ui->SetLifepoints->addItem("4000");
    ui->SetLifepoints->addItem("8000");
    ui->SetLifepoints->addItem("10000");
    ui->SetLifepoints->addItem("16000");


    ui->SetTimePerMove->addItem("3");
    ui->SetTimePerMove->addItem("5");
    ui->SetTimePerMove->addItem("10");
    ui->SetTimePerMove->addItem("20");
    ui->SetTimePerMove->addItem("30");

    ui->SetInitialNumberOfCards->addItem("5");
    ui->SetInitialNumberOfCards->addItem("6");
    ui->SetInitialNumberOfCards->addItem("7");
    ui->SetInitialNumberOfCards->addItem("8");
    ui->SetInitialNumberOfCards->addItem("9");
    ui->SetInitialNumberOfCards->addItem("10");

    connect(ui->okButton , &QPushButton::clicked , this, &GameSettings::onOkButtonClick);

    connect(ui->leaveButton, &QPushButton::clicked, this, &GameSettings::onLeaveButtonClick);

}

GameSettings::~GameSettings()
{
    delete ui;
}

int GameSettings::getTimePerMove() const
{
    return timePerMove;
}

void GameSettings::setTimePerMove(int newTimePerMove)
{
    timePerMove = newTimePerMove;
}

int GameSettings::getNumberOfCards() const
{
    return numberOfCards;
}

int GameSettings::getLifePoints() const
{
    return lifePoints;
}

void GameSettings::setLifePoints(int newLifePoints){
    lifePoints = newLifePoints;
}

void GameSettings::setNumberOfCards(int newNumberOfCards)
{
    numberOfCards = newNumberOfCards;
}



void GameSettings::onSetLifepointsCurrentIndexChanged(int index)
{
    switch (index) {
    case 0:
        lifePoints = 2000;
        break;
    case 1:
        lifePoints = 4000;
        break;
    case 2:
        lifePoints = 8000;
        break;
    case 3:
        lifePoints = 10000;
        break;
    case 4:
        lifePoints = 16000;
        break;
    default:
        lifePoints = 4000;
        break;
    }
}


void GameSettings::onSetTimePerMoveCurrentIndexChanged(int index)
{
    switch (index) {
    case 0:
        timePerMove = 3;
        break;
    case 1:
        timePerMove = 5;
        break;
    case 2:
        timePerMove =10;
        break;
    case 3:
        timePerMove= 20;
        break;
    case 4:
        timePerMove = 30;
        break;
    default:
        timePerMove = 5;
        break;
    }
}


void GameSettings::onSetInitialNumberOfCardsCurrentIndexChanged(int index)
{
    switch (index) {
    case 0:
        numberOfCards = 5;
        break;
    case 1:
        numberOfCards = 6;
        break;
    case 2:
        numberOfCards =7;
        break;
    case 3:
        numberOfCards= 8;
        break;
    case 4:
        numberOfCards = 9;
        break;
    case 5:
        numberOfCards = 10;
        break;
    default:
        numberOfCards = 5;
        break;
    }

}



void GameSettings::onOkButtonClick()
{
    emit okButtonClicked();
    std:: cout << "ssss" << std:: endl ;
    close();
}

void GameSettings::onLeaveButtonClick(){
    close();
}
