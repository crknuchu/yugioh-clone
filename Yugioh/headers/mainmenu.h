#ifndef MAINMENU_H
#define MAINMENU_H

#include <QJsonObject>
#include <QJsonDocument>
#include <QMainWindow>
#include "headers/Game.h"
#include "headers/GameSettings.h"
#include "qmediaplayer.h"

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

    void saveDeckSettingsJson(int lifePoints,int numberOfCards,int timePerMove);


private slots:
    void onStartButtonClick();

    void on_btnQuit_clicked();

    void on_btnGameSettings_clicked();

    void updateValues();

    void on_btnMusic_clicked();

private:
    Ui::MainMenu *ui;
    Game *m_pGame;
    GameSettings *m_pGameSettings;
    QMediaPlayer *music;
    bool musicActive=true;
};



#endif // MAINMENU_H
