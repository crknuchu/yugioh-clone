#ifndef PROFILESETTINGS_H
#define PROFILESETTINGS_H

#include <QWidget>

namespace Ui {
class profileSettings;
}

class profileSettings : public QWidget {
  Q_OBJECT

public:
  explicit profileSettings(QWidget *parent = nullptr);
  ~profileSettings();

private:
  Ui::profileSettings *ui;
};

#endif // PROFILESETTINGS_H
