#include "decksettings.h"
#include "ui_decksettings.h"

deckSettings::deckSettings(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::deckSettings)
{
    ui->setupUi(this);
    QPixmap bkgnd(":/resources/pictures/background.jpg");
    bkgnd = bkgnd.scaled(this->size(), Qt::IgnoreAspectRatio);
    QPalette palette;
    palette.setBrush(QPalette::Window, bkgnd);
    this->setPalette(palette);

}

deckSettings::~deckSettings()
{
    delete ui;
}
