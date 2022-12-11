#include "headers/mainmenu.h"
#include "ui_mainmenu.h"
#include "headers/Game.h"
#include "headers/Player.h"
 #include <QDir>
MainMenu::MainMenu(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainMenu)
{
    ui->setupUi(this);
    QPixmap bkgnd(":/resources/yugioh1.jpg");
    //bkgnd.devicePixelRatioFScale();
    bkgnd = bkgnd.scaled(this->size(), Qt::IgnoreAspectRatio);
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

    //Player player1("Nikola");
    //Player player2("Milan");
    //game = new Game(player1,player2);
    //Game game(player1, player2);
    //game->show();
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

