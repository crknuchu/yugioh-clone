#ifndef GAMESETTINGS_H
#define GAMESETTINGS_H

#include <QDialog>
#include <QDesktopServices>
#include <QUrl>


enum class Decks
{
    YUGI,
    KAIBA
};

enum class LifePoints
{
    MINIMAL_POINTS,
    SMALLER_POINTS,
    STANDARD_POINTS,
    BIGGER_POINTS,
    MAXIMUM_POINTS
};



enum class TimePerMove
{
    MINIMAL_TIME,
    SMALLER_TIME,
    STANDARD_TIME,
    BIGGER_TIME,
    MAXIMUM_TIME
};

enum class NumberOfCards
{
    MINIMAL_CARDS,
    SMALLER_CARDS,
    STANDARD_CARDS,
    BIGGER_CARDS,
    MAXIMUM_CARDS
};


namespace Ui {
class GameSettings;
}

class GameSettings : public QDialog
{
    Q_OBJECT

public:
    explicit GameSettings(QWidget *parent = nullptr);
    ~GameSettings();



    TimePerMove getTimePerMove() const;
    void setTimePerMove(TimePerMove newTimePerMove);

    NumberOfCards getNumberOfCards() const;
    void setNumberOfCards(NumberOfCards newNumberOfCards);

    LifePoints getLifePoints() const;
    void setLifePoints(LifePoints newLifePoints);

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


    void on_ChooseDeck_activated(int index);



private:
    TimePerMove timePerMove ;
    NumberOfCards numberOfCards ;
    LifePoints lifePoints ;
    Decks deck;
    Ui::GameSettings *ui;
};

#endif // GAMESETTINGS_H
