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
    extern Card *pCardToBePlacedOnField;
    extern Card *pAttackingMonster;
    extern Card *pCardToBeReturned;
}





class Game: public QMainWindow
{
    Q_OBJECT

public:
  Game();
  Game(Player p1, Player p2,int lifePoints = 4000,int numberOfCards = 5 ,int timePerMove = 5,QWidget *parent = nullptr );  // Why is parent's type QWidget and not QMainWindow?
  ~Game();
  int lifePoints ;
  int numberOfCards ;
  int timePerMove ;


  // Public member functions:
  void start();
  GamePhases setGamePhase() const;





  int getLifePoints() const;
  void setLifePoints(int newLifePoints);

  int getNumberOfCards() const;
  void setNumberOfCards(int newNumberOfCards);

  int getTimePerMove() const;
  void setTimePerMove(int newTimePerMove);

private:
  Ui::MainWindow *ui;
  QGraphicsScene *scene;
  GamePhases m_phase;
  Player m_player1;  
  Player m_player2;
  int m_currentTurn;
  int counter = 0;

  int resizeCount = 0; // dirty hack



  // Private member functions:
  int randomGenerator(const int limit) const;
  int decideWhoPlaysFirst() const;
  void firstTurnSetup(float, float);
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
    void onActivateFromHand(Card &);


    // Slots for Card signal handling
    void onCardHoverEnter(Card &);
    void onCardHoverLeave(Card &);
    void onCardSelect(Card *);


    // Slots for CardMenu signal handling
    void onActivateButtonClick(Card &);
    void onSetButtonClick(const Card &);
    void onSummonButtonClick(Card &);
    void onAttackButtonClick(Card &);

    // Slots for EffectActivator signal handling
    void onHealthPointsChange(Player &);
    void onGameEnd(Player &); // const?
    void onMonsterReborn(Player &);
    void onChangeOfHeart(Player &, Player &);

    // Slots for Zone signal handling
    void onRedZoneClick(Zone *zone);
    void onGreenZoneClick(Zone *zone);

    void onReturnCardToOpponent();

signals:
    void returnCardToOpponent();
    void mainWindowResized(QResizeEvent *);
    void gamePhaseChanged(const GamePhases &newGamePhase);
    void turnEnded();
    void gameEndedAfterBattle(Player &loser);
    void activateFromHand(Card &);
};






#endif // GAME_H
