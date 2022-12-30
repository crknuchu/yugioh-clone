#include "headers/DeckSettings.h"
#include "headers/ui_decksettings.h"

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
