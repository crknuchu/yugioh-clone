#include "headers/mainmenu.h"
#include "ui_mainmenu.h"
#include "headers/Game.h"
#include "headers/Player.h"
#include "headers/GameSettings.h"
#include <QDir>
#include <QScreen>

MainMenu::MainMenu(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainMenu)
{
    ui->setupUi(this);
    QPixmap bkgnd(":/resources/menubackground.png");
    QScreen *screen = QGuiApplication::primaryScreen();
    QRect  screenGeometry = screen->geometry();
    int height = screenGeometry.height();
    int width = screenGeometry.width();

    bkgnd = bkgnd.scaled(width,height, Qt::KeepAspectRatioByExpanding);
    QPalette palette;
    palette.setBrush(QPalette::Window, bkgnd);
    this->setPalette(palette);
}

MainMenu::~MainMenu()
{
    delete ui;
}

void MainMenu::on_pushButton_clicked()
{

    Player player1("Nikola");
    Player player2("Milan");
    game = new Game(player1,player2);

    game->showFullScreen();

    //FIX THIS
    //Player player1("Nikola");
    //Player player2("Milan");
    //std::cout << GameSettings::lifePoints;
   //this->setGame(new Game(player1,player2))


    close(); //mozda ne treba
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
    game = newGame;
}

