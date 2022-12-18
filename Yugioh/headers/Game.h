#ifndef GAME_H
#define GAME_H

#include "Player.h"
#include "Card.h"

#include <QGraphicsScene>
#include <QMainWindow>
#include <QResizeEvent>

// WIP
#include "GamePhase.h"


#include "Zone.h"
namespace Ui {
    class MainWindow;
}


class Card;





/* TODO:
 * 1) GamePhasesEnum.h to avoid Game.h includes in other files
 * 2)Unnamed namespaces
 */



// Unnamed namespaces as a replacement for global static variables
//namespace {
//    Player *m_pCurrentPlayer;
//    Player *m_pOtherPlayer;
//}



// Will be needed in the future for the Summoning action
//static int *p_Summon_target = nullptr;


class Game: public QMainWindow
{
    Q_OBJECT

public:
  Game();
  Game(Player p1, Player p2, QWidget *parent = nullptr);  // Why is parent's type QWidget and not QMainWindow?
  ~Game();



  // Public member functions:
  void start();
  GamePhasesEnum getGamePhase() const;



private:
  Ui::MainWindow *ui;
  QGraphicsScene *scene;
  GamePhasesEnum m_phase;
  Player m_player1;  
  Player m_player2;
  Player *m_pCurrentPlayer;
  Player *m_pOtherPlayer;
  int m_currentTurn;
  int counter = 0;

  // Private member functions:
  int randomGenerator(const int limit) const;
  int decideWhoPlaysFirst() const;
  void firstTurnSetup(float, float);
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
    void onGamePhaseChange(const GamePhasesEnum &newGamePhase);
    void onTurnEnd();
    void onRedZoneClicked(Zone* zone);

    /*
     * This Card* will eventually be replaced with Player * probably,
     * because in the future Game will only have info about Player,
     * who will manage adding the card to the scene.
     * For now, cards are added to the scene in Game.cpp for test purposes
     * so this is a good enough placeholder until we change that.
     */


    void onCardAddedToScene(const Card *);



    // FIXME: Slots for signals emitted in Card.cpp
//    void onCardHover(Card *);



    // Slots for CardMenu signal handling
    void onActivateButtonClick(const Card &);
    void onSetButtonClick(const Card &);
    void onSummonButtonClick(const Card &);

signals:
    void mainWindowResized(QResizeEvent *);
    void gamePhaseChanged(const GamePhasesEnum &newGamePhase);
    void turnEnded();
    void cardAddedToScene(Card *);
};






#endif // GAME_H
