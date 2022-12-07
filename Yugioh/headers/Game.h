#ifndef GAME_H
#define GAME_H

#include "Player.h"
#include "Card.h"

#include <QGraphicsScene>
#include <QMainWindow>
#include <QResizeEvent>

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

class Game: public QMainWindow
{
    Q_OBJECT

public:
  Game();
  Game(Player p1, Player p2, QWidget *parent = nullptr);  // Why is parent's type QWidget and not QMainWindow?
  ~Game();
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
  void switchPlayers();

// QT related stuff:
  int m_windowWidth;
  int m_windowHeight;

  void setupConnections();
  bool eventFilter(QObject *obj, QEvent *event) override;


private slots:
    void onBattlePhaseButtonClick();
    void onMainPhase2ButtonClick();
    void onEndPhaseButtonClick();
    void onMainWindowResize(QResizeEvent *);
    void onGamePhaseChange(const GamePhases &newGamePhase);
    void onTurnEnd();


    /*
     * This Card* will eventually be replaced with Player * probably,
     * because in the future Game will only have info about Player,
     * who will manage adding the card to the scene.
     * For now, cards are added to the scene in Game.cpp for test purposes
     * so this is a good enough placeholder until we change that.
     */
    void onCardAddedToScene(const Card *);

    // Slots for CardMenu signal handling
    void onActivateButtonClick(const Card *);
    void onSetButtonClick(const Card *);

signals:
    void mainWindowResized(QResizeEvent *);
    void gamePhaseChanged(const GamePhases &newGamePhase);
    void turnEnded();
    void cardAddedToScene(Card *);
};






#endif // GAME_H
