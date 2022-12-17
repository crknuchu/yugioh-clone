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
    Game g;

    void setGame(Game *newGame);

    void setMusic();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_5_clicked();

    void on_pushButton_5_released();



private:
    Ui::MainMenu *ui;
    Game *game;
    GameSettings *gameSettings;
};



#endif // MAINMENU_H
