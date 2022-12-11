#ifndef GAME_H
#define GAME_H

#include "Player.h"
#include <QGraphicsScene>
#include <QMainWindow>
#include "Zone.h"
namespace Ui {
    class MainWindow;
}


enum class GamePhases {
  DRAW_PHASE,
  STANDBY_PHASE,
  MAIN_PHASE1,
  BATTLE_PHASE,
  MAIN_PHASE2,
  END_PHASE
};

class Card;

class Game: public QMainWindow
{
    Q_OBJECT

public:
  Game();
  Game(Player p1, Player p2, QWidget *parent = nullptr);  // Why is parent's type QWidget and not QMainWindow?
  ~Game();
  GamePhases gamePhase;
  GamePhases getGamePhase()const;

  // Public member functions:
  void start();

private:
  Ui::MainWindow *ui;
  QGraphicsScene *scene;

  Player m_player1;
  Player m_player2;
  Player *m_pCurrentPlayer;
  Player *m_pOtherPlayer;
  GamePhases m_currentGamePhase;
  int m_currentTurn;

  // Private member functions:
  int randomGenerator(const int limit) const;
  int decideWhoPlaysFirst() const;
  void firstTurnSetup();
  void playFirstTurn();
  void switchPlayers();
  void playTurn();


// QT related stuff:
  void setupConnections();

private slots:
    void btnBattlePhaseClicked();
    void btnMainPhase2Clicked();
    void btnEndPhaseClicked();
    void onRedZoneClicked(Zone* zone);
};






#endif // GAME_H
