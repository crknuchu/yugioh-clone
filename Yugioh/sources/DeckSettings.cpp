#include "headers/DeckSettings.h"
#include "ui_decksettings.h"

deckSettings::deckSettings(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::deckSettings)
{
    ui->setupUi(this);
}

deckSettings::~deckSettings()
{
    delete ui;
}
