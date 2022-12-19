#include "headers/mainmenu.h"
#include "ui_mainmenu.h"
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
    QMediaPlayer * music = new QMediaPlayer();
    music->setMedia(QUrl("qrc:/resources/sounds/illusion.mp3"));
    music->play();


}

MainMenu::~MainMenu()
{
    delete ui;
}

void MainMenu::on_pushButton_clicked()
{

    Player* player1 = new Player("Nikola");
    Player* player2 = new Player("Milan");
    m_pGame = new Game(*player1, *player2);
    m_pGame->showFullScreen();
}


void MainMenu::on_pushButton_4_clicked()
{
    close();
}


void MainMenu::on_pushButton_5_clicked()
{
    gameSettings = new GameSettings();
    gameSettings->show();

}



void MainMenu::setGame(Game *newGame)
{
    m_pGame = newGame;
}








