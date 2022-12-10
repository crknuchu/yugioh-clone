#ifndef GAMESETTINGS_H
#define GAMESETTINGS_H

#include <QDialog>

namespace Ui {
class GameSettings;
}

class GameSettings : public QDialog
{
    Q_OBJECT

public:
    explicit GameSettings(QWidget *parent = nullptr);
    ~GameSettings();

private:
    Ui::GameSettings *ui;
};

#endif // GAMESETTINGS_H
