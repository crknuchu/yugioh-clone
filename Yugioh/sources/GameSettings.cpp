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
    ui->SetTimePerMove->addItem("6");
    ui->SetTimePerMove->addItem("10");
    ui->SetTimePerMove->addItem("20");

    ui->SetInitialNumberOfCards->addItem("3");
    ui->SetInitialNumberOfCards->addItem("4");
    ui->SetInitialNumberOfCards->addItem("5");
    ui->SetInitialNumberOfCards->addItem("6");
    ui->SetInitialNumberOfCards->addItem("7");



    ui->ChooseDeck->addItem("Yugi's deck");
    ui->ChooseDeck->addItem("Kaiba's deck");


    connect(ui->leaveButton, &QPushButton::clicked, this, &GameSettings::onLeaveButtonClick);


    connect(ui->help,&QPushButton::clicked, this, &GameSettings::onHelpButtonClick);
}

GameSettings::~GameSettings()
{
    delete ui;
}



const QMap<LifePoints, int> GameSettings::getLifePointsEnumToInt{
    {LifePoints::MINIMAL_POINTS, 2000},
    {LifePoints::SMALLER_POINTS, 4000},
    {LifePoints::STANDARD_POINTS, 8000},
    {LifePoints::BIGGER_POINTS, 10000},
    {LifePoints::MAXIMUM_POINTS, 16000}
};

const QMap<NumberOfCards, int> GameSettings::getNumberOfCardsEnumToInt{
    {NumberOfCards::MINIMAL_CARDS, 3},
    {NumberOfCards::SMALLER_CARDS, 4},
    {NumberOfCards::STANDARD_CARDS, 5},
    {NumberOfCards::BIGGER_CARDS, 6},
    {NumberOfCards::MAXIMUM_CARDS, 7}
};


const QMap<TimePerMove, int> GameSettings::getTimePerMoveEnumToInt{
   {TimePerMove::MINIMAL_TIME, 3},
   {TimePerMove::SMALLER_TIME, 5},
   {TimePerMove::STANDARD_TIME, 6},
   {TimePerMove::BIGGER_TIME, 10},
   {TimePerMove::MAXIMUM_TIME , 20}
};

const QMap<Decks,QString> GameSettings::getDeckEnumToString{
    {Decks::KAIBA, "KAIBA"},
    {Decks::YUGI, "YUGI" }
};


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


//void GameSettings::on_ChooseDeck_activated(int index)
//{
//    switch (index) {
//    case 0:
//        this->deck = Decks::YUGI;
//        break;
//    case 1:
//        this->deck = Decks::KAIBA;
//        break;
//    default:
//        this->deck = Decks::YUGI;
//        break;
//    }
//}


void GameSettings::saveGameSettingsJson(int lifePoints,int numberOfCards,int timePerMove, QString deck)
{
    QJsonObject obj;
    obj.insert("lifepoints",lifePoints);
    obj.insert("numberofcards",numberOfCards);
    obj.insert("timepermove",timePerMove);
    obj.insert("deck", deck);
    QString path = qApp->applicationDirPath();
    path.append("/resources/deck_settings.json");

    QFile file;
    file.setFileName(path);
    file.open(QIODevice::WriteOnly | QIODevice::Text);
    QJsonDocument d(obj);
    file.write(d.toJson());
    file.close();
    return;
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


void GameSettings::on_okButton_clicked()
{

    saveGameSettingsJson( getLifePointsEnumToInt[this->lifePoints]  ,getNumberOfCardsEnumToInt[this->numberOfCards],getTimePerMoveEnumToInt[this->timePerMove],getDeckEnumToString[this->deck]);
    close();
}




void GameSettings::on_SetLifepoints_activated(int index)
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


void GameSettings::on_SetTimePerMove_activated(int index)
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


void GameSettings::on_SetInitialNumberOfCards_activated(int index)
{
    switch (index) {
    case 0:
        numberOfCards = NumberOfCards::MINIMAL_CARDS;
        break;
    case 1:
        numberOfCards = NumberOfCards::SMALLER_CARDS;
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


void GameSettings::on_ChooseDeck_currentIndexChanged(int index)
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

