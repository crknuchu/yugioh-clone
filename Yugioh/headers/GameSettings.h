#ifndef GAMESETTINGS_H
#define GAMESETTINGS_H
#include <QDesktopServices>
#include <QDialog>
#include <QJsonDocument>
#include <QJsonObject>
#include <QUrl>
#include <qfile.h>

enum class Decks { YUGI, KAIBA };

enum class LifePoints {
  MINIMAL_POINTS,
  SMALLER_POINTS,
  STANDARD_POINTS,
  BIGGER_POINTS,
  MAXIMUM_POINTS
};

enum class TimePerMove { MINIMAL_TIME, SMALLER_TIME, STANDARD_TIME, BIGGER_TIME, MAXIMUM_TIME };

enum class NumberOfCards {
  MINIMAL_CARDS,
  SMALLER_CARDS,
  STANDARD_CARDS,
  BIGGER_CARDS,
  MAXIMUM_CARDS
};

namespace Ui {
class GameSettings;
}

class GameSettings : public QDialog {
  Q_OBJECT

public:
  explicit GameSettings(QWidget* parent = nullptr);
  ~GameSettings();

  TimePerMove getTimePerMove() const;
  void setTimePerMove(TimePerMove newTimePerMove);

  NumberOfCards getNumberOfCards() const;
  void setNumberOfCards(NumberOfCards newNumberOfCards);

  LifePoints getLifePoints() const;
  void setLifePoints(LifePoints newLifePoints);

  static const QMap<TimePerMove, int> getTimePerMoveEnumToInt;
  static const QMap<NumberOfCards, int> getNumberOfCardsEnumToInt;
  static const QMap<LifePoints, int> getLifePointsEnumToInt;
  static const QMap<Decks, QString> getDeckEnumToString;

signals:
  void okButtonClicked();
  void helpClicked();

public slots:

  void onLeaveButtonClick();

  void onHelpButtonClick();

  // void on_ChooseDeck_activated(int index);

  void on_okButton_clicked();

  void on_SetLifepoints_activated(int index);

  void on_SetTimePerMove_activated(int index);

  void on_SetInitialNumberOfCards_activated(int index);

  void on_ChooseDeck_currentIndexChanged(int index);

private:
  void saveGameSettingsJson(int lifePoints, int numberOfCards, int timePerMove, QString deck);
  TimePerMove timePerMove;
  NumberOfCards numberOfCards;
  LifePoints lifePoints;
  Decks deck;
  Ui::GameSettings* ui;
};

#endif // GAMESETTINGS_H
