#include "headers/mainmenu.h"
#include "headers/ui_mainmenu.h"
#include "headers/Game.h"
#include "headers/Player.h"
#include "headers/GameSettings.h"
#include <QDir>
#include <QScreen>
#include <QMediaPlayer>


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
//    QMediaPlayer * music = new QMediaPlayer();
//    music->setSaource(QUrl("qrc:/resources/sounds/illusion.mp3")); // in qt5 is setMedia()
//    music->play();


}

MainMenu::~MainMenu()
{
    delete ui;
    delete m_pGame;
    delete m_pGameSettings;
}

void MainMenu::on_btnStart_clicked()
{
    Player* player1 = new Player("Nikola");
    Player* player2 = new Player("Milan");
    m_pGame = new Game(*player1, *player2);
    m_pGame->showFullScreen();
}


void MainMenu::on_btnQuit_clicked()
{
    close();
}

void MainMenu::on_btnGameSettings_clicked()
{
    m_pGameSettings = new GameSettings();
    m_pGameSettings->show();

    connect(m_pGameSettings, &GameSettings::okButtonClicked, this, &MainMenu::updateValues);
}

void MainMenu::setGame(Game *newGame)
{
    m_pGame = newGame;
}

void MainMenu::updateValues()
{
    //to do save as json file?
    if(!m_pGame)
    {
        m_pGame->setLifePoints(m_pGameSettings->getLifePoints());
        m_pGame->setNumberOfCards(m_pGame->getNumberOfCards());
        m_pGame->setTimePerMove(m_pGame->getTimePerMove());
    }
}

void MainMenu::saveDeckSettingsJson(int lifePoints,int numberOfCards,int timePerMove)
{
    QJsonObject obj;
    obj.insert("lifepoints",lifePoints);
    obj.insert("numberofcards",numberOfCards);
    obj.insert("timepermove",timePerMove);

    QString path = qApp->applicationDirPath();
    path.append("/resources/deck_settings.json");
    qWarning() << path;

    QFile file;
    file.setFileName(path);
    file.open(QIODevice::WriteOnly | QIODevice::Text);
    QJsonDocument d(obj);
    file.write(d.toJson());
    file.close();
    return;
}

