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







// Will be needed in the future for the Summoning action
//static int *p_Summon_target = nullptr;

// WIP
namespace GameExternVars {
    extern Player *pCurrentPlayer;
    extern Player *pOtherPlayer;
    extern Card *pSummonTarget;
    extern Card *pAttackingMonster;
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
  GamePhases setGamePhase() const;





private:
  Ui::MainWindow *ui;
  QGraphicsScene *scene;
  GamePhases m_phase;
  Player m_player1;  
  Player m_player2;
  int m_currentTurn;


  // Private member functions:
  int randomGenerator(const int limit) const;
  int decideWhoPlaysFirst() const;
  void firstTurnSetup();
  void switchPlayers();

  void damageCalculation(Card *attackingMonster, Card *attackedMonster);
  void battleBetweenTwoAttackPositionMonsters(MonsterCard &attacker, MonsterCard &defender);
  void battleBetweenTwoDifferentPositionMonsters(MonsterCard &attacker, MonsterCard &defender);
  void damagePlayer(Player &targetPlayer, int howMuch);

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
    void onCardAddedToScene(Card &);


    // Slots for Card signal handling
    void onCardHoverEnter(Card &);
    void onCardHoverLeave(Card &);
    void onCardSelect(Card *);


    // Slots for CardMenu signal handling
    void onActivateButtonClick(const Card &);
    void onSetButtonClick(const Card &);
    void onSummonButtonClick(Card &);
    void onAttackButtonClick(Card &);

    // Slots for EffectActivator signal handling
    void onHealthPointsChange(Player &);
    void onGameEnd(Player &); // const?

    // Slots for Zone signal handling
    void onRedZoneClick(Zone *zone);
    void onGreenZoneClick(Zone *zone);


signals:
    void mainWindowResized(QResizeEvent *);
    void gamePhaseChanged(const GamePhases &newGamePhase);
    void turnEnded();
    void cardAddedToScene(Card &targetCard);
    void gameEndedAfterBattle(Player &loser);
};






#endif // GAME_H
