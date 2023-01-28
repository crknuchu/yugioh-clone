#include "headers/DeckSettings.h"
//#include "headers/ui_decksettings.h"
#include "ui_DeckSettings.h"
deckSettings::deckSettings(QWidget* parent) : QDialog(parent), ui(new Ui::deckSettings) {
  ui->setupUi(this);
}

deckSettings::~deckSettings() { delete ui; }
