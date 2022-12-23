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

    void setGame(Game *newGame);




private slots:
    void on_start_clicked();

    void on_quit_clicked();

    void on_gameSettings_clicked();

     void updateValues();



private:
    GameSettings *gameSetting;
    Ui::MainMenu *ui;
    Game *m_pGame;
    GameSettings *gameSettings;
};



#endif // MAINMENU_H
