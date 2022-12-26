#ifndef MAINMENU_H
#define MAINMENU_H

#include <QMainWindow>
#include "headers/Game.h"
#include "headers/GameSettings.h"

namespace Ui {
class MainMenu;
}

class MainMenu : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainMenu(QWidget *parent = nullptr);
    ~MainMenu();

    void setupConnections();

private slots:
    void on_btnStart_clicked();

    void on_btnQuit_clicked();

    void on_btnGameSettings_clicked();

private:
    Ui::MainMenu *ui;
    Game *game;
    GameSettings *gameSettings;
};

#endif // MAINMENU_H
