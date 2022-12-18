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
    int lifePoints = 4000;
    int timePerMove = 5;
    int numberOfCards = 5;




private slots:
    void on_SetLifepoints_currentIndexChanged(int index);

    void on_SetTimePerMove_currentIndexChanged(int index);

    void on_SetInitialNumberOfCards_currentIndexChanged(int index);

//    void on_Back_accepted();

    void on_Back_rejected();

private:
    Ui::GameSettings *ui;
};

#endif // GAMESETTINGS_H
