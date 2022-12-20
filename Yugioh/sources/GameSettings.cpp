#include "headers/GameSettings.h"
#include "ui_GameSettings.h"

GameSettings::GameSettings(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::GameSettings)
{
    ui->setupUi(this);

    QPixmap bkgnd(":/resources/background.jpg");
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

}

GameSettings::~GameSettings()
{
    delete ui;
}