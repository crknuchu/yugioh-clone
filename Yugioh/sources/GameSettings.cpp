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


    ui->ChooseDeck->addItem("Yugi's deck");
    ui->ChooseDeck->addItem("Kaiba's deck");

    connect(ui->okButton , &QPushButton::clicked , this, &GameSettings::onOkButtonClick);

    connect(ui->leaveButton, &QPushButton::clicked, this, &GameSettings::onLeaveButtonClick);


    connect(ui->help,&QPushButton::clicked, this, &GameSettings::onHelpButtonClick);
}

GameSettings::~GameSettings()
{
    delete ui;
}




void GameSettings::onSetLifepointsCurrentIndexChanged(int index)
{
    switch (index) {
    case 0:
        lifePoints = LifePoints::MINIMAL_POINTS;
        break;
    case 1:
        lifePoints = LifePoints::SMALLER_POINTS;
        break;
    case 2:
        lifePoints = LifePoints::STANDARD_POINTS;
        break;
    case 3:
        lifePoints = LifePoints::BIGGER_POINTS;
        break;
    case 4:
        lifePoints = LifePoints::MAXIMUM_POINTS;
        break;
    default:
        lifePoints = LifePoints::STANDARD_POINTS;
        break;
    }
}


void GameSettings::onSetTimePerMoveCurrentIndexChanged(int index)
{
    switch (index) {
    case 0:
        timePerMove = TimePerMove::MINIMAL_TIME;
        break;
    case 1:
        timePerMove = TimePerMove::SMALLER_TIME;
        break;
    case 2:
        timePerMove =TimePerMove::STANDARD_TIME;
        break;
    case 3:
        timePerMove= TimePerMove::BIGGER_TIME;
        break;
    case 4:
        timePerMove = TimePerMove::MAXIMUM_TIME;
        break;
    default:
        timePerMove = TimePerMove::STANDARD_TIME;
        break;
    }
}


void GameSettings::onSetInitialNumberOfCardsCurrentIndexChanged(int index)
{
    switch (index) {
    case 0:
        numberOfCards = NumberOfCards::MINIMAL_CARDS;
        break;
    case 1:
        numberOfCards = NumberOfCards::SMALLER_CARDS;;
        break;
    case 2:
        numberOfCards =NumberOfCards::STANDARD_CARDS;
        break;
    case 3:
        numberOfCards= NumberOfCards::BIGGER_CARDS;
        break;
    case 4:
        numberOfCards = NumberOfCards::MAXIMUM_CARDS;
        break;
    default:
        numberOfCards = NumberOfCards::STANDARD_CARDS;
        break;
    }

}



void GameSettings::onOkButtonClick()
{
    emit okButtonClicked();
    close();
}

void GameSettings::onLeaveButtonClick(){
    close();
}

void GameSettings::onHelpButtonClick()
{
    emit helpClicked();
    QString link = "https://www.dicebreaker.com/games/yu-gi-oh-tcg/how-to/how-to-play-yu-gi-oh-tcg#how-to-play-ygo-tcg";
    QDesktopServices:: openUrl(QUrl(link));
    close();
}


void GameSettings::on_ChooseDeck_activated(int index)
{
    switch (index) {
    case 0:
        this->deck = Decks::YUGI;
        break;
    case 1:
        this->deck = Decks::KAIBA;
        break;
    default:
        this->deck = Decks::YUGI;
        break;
    }
}

LifePoints GameSettings::getLifePoints() const
{
    return lifePoints;
}

void GameSettings::setLifePoints(LifePoints newLifePoints)
{
    lifePoints = newLifePoints;
}

NumberOfCards GameSettings::getNumberOfCards() const
{
    return numberOfCards;
}

void GameSettings::setNumberOfCards(NumberOfCards newNumberOfCards)
{
    numberOfCards = newNumberOfCards;
}

TimePerMove GameSettings::getTimePerMove() const
{
    return timePerMove;
}

void GameSettings::setTimePerMove(TimePerMove newTimePerMove)
{
    timePerMove = newTimePerMove;
}

