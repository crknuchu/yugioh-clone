#include "headers/mainmenu.h"
#include "headers/ui_mainmenu.h"
#include "headers/Game.h"
#include "headers/Player.h"

#include <QDir>
MainMenu::MainMenu(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainMenu)
{
    ui->setupUi(this);

    setupConnections();


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

void MainMenu::setupConnections()
{
    // TODO: Refactor other error-prone on_foo_bar() functions
//    connect(ui->btnConnect, &QPushButton::clicked, this, &MainMenu::onConnectButtonClick);
}

void MainMenu::on_btnStart_clicked()
{
    Player *player1 = new Player("Nikola");
    Player *player2 = new Player("Milan");
    game = new Game(*player1, *player2);

    game->show();
}


void MainMenu::on_btnQuit_clicked()
{
    close();
}


void MainMenu::on_btnGameSettings_clicked()
{
    gameSettings = new GameSettings();
    gameSettings->show();

}

