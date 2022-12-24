#ifndef GAMESETTINGS_H
#define GAMESETTINGS_H

#include <QDialog>
#include <QDesktopServices>
#include <QUrl>

namespace Ui {
class GameSettings;
}

class GameSettings : public QDialog
{
    Q_OBJECT

public:
    explicit GameSettings(QWidget *parent = nullptr);
    ~GameSettings();

    int timePerMove ;
    int numberOfCards ;
    int lifePoints ;



    int getLifePoints() const;
    void setLifePoints(int newLifePoints);

    int getNumberOfCards() const;
    void setNumberOfCards(int newNumberOfCards);

    int getTimePerMove() const;
    void setTimePerMove(int newTimePerMove);

signals:
    void okButtonClicked();
    void helpClicked();

private slots:
    void onSetLifepointsCurrentIndexChanged(int index);

    void onSetTimePerMoveCurrentIndexChanged(int index);

    void onSetInitialNumberOfCardsCurrentIndexChanged(int index);

    void onOkButtonClick();

    void onLeaveButtonClick();



    void onHelpButtonClick();

private:
    Ui::GameSettings *ui;
};

#endif // GAMESETTINGS_H
