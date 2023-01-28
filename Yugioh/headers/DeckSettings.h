#ifndef DECKSETTINGS_H
#define DECKSETTINGS_H

#include <QDialog>

namespace Ui {
class deckSettings;
}

class deckSettings : public QDialog {
  Q_OBJECT

public:
  explicit deckSettings(QWidget* parent = nullptr);
  ~deckSettings();

private:
  Ui::deckSettings* ui;
};

#endif // DECKSETTINGS_H
