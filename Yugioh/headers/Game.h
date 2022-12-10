#ifndef GAME_H
#define GAME_H

#include "Player.h"
#include "Card.h"

#include <QGraphicsScene>
#include <QMainWindow>
#include <QResizeEvent>

// WIP
#include "GamePhase.h"


namespace Ui {
    class MainWindow;
}


class Card;







// Will be needed in the future for the Summoning action
//static int *p_Summon_target = nullptr;

// WIP
namespace GameExternVars {
    extern Player *m_pCurrentPlayer;
    extern Player *m_pOtherPlayer;
}





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



    // FIXME: Slots for signals emitted in Card.cpp
    void onCardHover(Card *);



    // Slots for CardMenu signal handling
    void onActivateButtonClick(const Card &);
    void onSetButtonClick(const Card &);
    void onSummonButtonClick(const Card &);

signals:
    void mainWindowResized(QResizeEvent *);
    void gamePhaseChanged(const GamePhases &newGamePhase);
    void turnEnded();
    void cardAddedToScene(Card *);
};






#endif // GAME_H
