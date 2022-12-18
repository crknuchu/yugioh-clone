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

void MainMenu::on_start_clicked()
{

    Player player1("Nikola");
    Player player2("Milan");
    //std::cout << GameSettings::lifePoints;
    this->setGame(new Game(player1,player2));
    //this->game->setLifePoints(gameSetting->getLifePoints());
    //this->game->setNumberOfCards(game->getNumberOfCards());
    //this->game->setTimePerMove(game->getTimePerMove());


    this->game->showFullScreen();

    std::cout << "hej" << this->game->lifePoints;



    }

void MainMenu::setGame(Game *newGame)
{
    game = newGame;
}



void MainMenu::on_quit_clicked()
{
    close();
}


void MainMenu::on_gameSettings_clicked()
{
    gameSetting = new GameSettings();
    gameSetting->show();

}

