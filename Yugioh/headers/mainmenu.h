#ifndef MAINMENU_H
#define MAINMENU_H

#include <QMainWindow>
#include "headers/Game.h"

namespace Ui {
class MainMenu;
}

class MainMenu : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainMenu(QWidget *parent = nullptr);
    ~MainMenu();

private slots:
    void on_pushButton_clicked();

private:
    Ui::MainMenu *ui;
    Game *game;
};

#endif // MAINMENU_H
