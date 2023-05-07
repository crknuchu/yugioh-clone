#include "headers/mainmenu.h"
#include "headers/ui_mainmenu.h"
#include "headers/Game.h"
#include "headers/Player.h"
#include "headers/GameSettings.h"
#include "headers/Serializer.h"
#include "headers/Deck.h"
#include <QDir>
#include <QScreen>
#include <QMediaPlayer>
//#include "headers/profilesettings.h"
#include "sources/profilesettings.h"

MainMenu::MainMenu(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainMenu)
{
    ui->setupUi(this);
    QPixmap bkgnd(":/resources/pictures/menubackground.png");
    QScreen *screen = QGuiApplication::primaryScreen();
    QRect  screenGeometry = screen->geometry();
    int height = screenGeometry.height();
    int width = screenGeometry.width();

    bkgnd = bkgnd.scaled(width,height, Qt::KeepAspectRatioByExpanding);
    QPalette palette;
    palette.setBrush(QPalette::Window, bkgnd);
    this->setPalette(palette);
    music = new QMediaPlayer();
    music->setMedia(QUrl("qrc:/resources/sounds/illusion.mp3")); // in qt5 is setMedia()
    music->play();
    musicActive = true;


    connect(ui->btnStart, &QPushButton::clicked, this, &MainMenu::onStartButtonClick);
    connect(ui->btnProfileSettings_2, &QPushButton::clicked, this, &MainMenu::on_btnProfileSettings_clicked);
}

MainMenu::~MainMenu()
{
    delete ui;
    if(m_pGame != nullptr)
      delete m_pGame;
    if(m_pGameSettings != nullptr)
      delete m_pGameSettings;
}

void MainMenu::onStartButtonClick()
{
   Serializer s1;
   Serializer s2;
   s1.loadFromJson(":/resources/yugi.json");
   s2.loadFromJson(":/resources/kaiba.json");
   Player* player1 = new Player("Nikola");
   Player* player2 = new Player("Milan");
   std::vector<Card*> yugiCards1 = s1.getCards();
   std::vector<Card*> yugiCards2 = s2.getCards();
   Deck d1 = Deck(yugiCards1);
   Deck d2 = Deck(yugiCards2);
   player1->setDeck(d1);
   player2->setDeck(d2);
   player1->setPlayerLifePoints(this->getLifePointsJson());
   player2->setPlayerLifePoints(this->getLifePointsJson());
   m_pGame = new Game(*player1, *player2,this->getLifePointsJson(),this->getNumberOfCardsJson(),this->getTimePerMoveJson());
   m_pGame->showFullScreen();
}

int MainMenu::getLifePointsJson(){
    QString val;
    QFile file;
    file.setFileName(":/resources/deck_settings.json");
    file.open(QIODevice::ReadOnly | QIODevice::Text);
    val = file.readAll();
    file.close();
    QJsonDocument d = QJsonDocument::fromJson(val.toUtf8());
    QJsonObject obj = d.object();

    int lifePoints = d["lifepoints"].toInt();
    qWarning() << lifePoints;
    return lifePoints;
}

int MainMenu::getNumberOfCardsJson(){
    QString val;
    QFile file;
    file.setFileName(":/resources/deck_settings.json");
    file.open(QIODevice::ReadOnly | QIODevice::Text);
    val = file.readAll();
    file.close();
    QJsonDocument d = QJsonDocument::fromJson(val.toUtf8());
    QJsonObject obj = d.object();

    int numberOfCards = d["numberofcards"].toInt();
    return numberOfCards;
}

int MainMenu::getTimePerMoveJson(){
    QString val;
    QFile file;
    file.setFileName(":/resources/deck_settings.json");
    file.open(QIODevice::ReadOnly | QIODevice::Text);
    val = file.readAll();
    file.close();
    QJsonDocument d = QJsonDocument::fromJson(val.toUtf8());
    QJsonObject obj = d.object();

    int timePerMove = d["timepermove"].toInt();
    return timePerMove;
}

QString MainMenu::getDeckJson(){
    QString val;
    QFile file;
    file.setFileName(":/resources/deck_settings.json");
    file.open(QIODevice::ReadOnly | QIODevice::Text);
    val = file.readAll();
    file.close();
    QJsonDocument d = QJsonDocument::fromJson(val.toUtf8());
    QJsonObject obj = d.object();

    QString deck = d["deck"].toString();
    return deck;
}

void MainMenu::on_btnQuit_clicked()
{
    close();
}

void MainMenu::on_btnProfileSettings_clicked(){

    profileSettings *p = new profileSettings();
    p->show();

    //need to update values after closing/saving
}

void MainMenu::on_btnGameSettings_clicked()
{
    m_pGameSettings = new GameSettings();
    m_pGameSettings->show();

}

void MainMenu::setGame(Game *newGame)
{
    m_pGame = newGame;
}


void MainMenu::on_btnMusic_clicked()
{

    if(!musicActive)
    {
    music->play();
    musicActive = true;
    ui->btnMusic->setText("MUSIC : ON");

    }
    else
    {
    music->stop();
    musicActive = false;
    ui->btnMusic->setText("MUSIC : OFF");
    }
}

