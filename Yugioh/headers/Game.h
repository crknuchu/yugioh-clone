#ifndef GAME_H
#define GAME_H

#include "Player.h"
#include "Card.h"
#include "GamePhase.h"
#include "Zone.h"

#include <QGraphicsScene>
#include <QMainWindow>
#include <QResizeEvent>
#include <QTcpSocket>

namespace Ui {
    class MainWindow;
}

namespace GameExternVars {
    extern Player *pCurrentPlayer;
    extern Player *pOtherPlayer;
    extern Card *pCardToBePlacedOnField;
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
  int resizeCount = 0; // dirty hack



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

// Networking:
  // TODO: Separate class?
  QTcpSocket *m_pTcpSocket = nullptr;
  QDataStream m_inDataStream;
  QString m_messageFromServer;

  bool writeData(QByteArray &data);
  QByteArray QInt32ToQByteArray(qint32 source); // We use qint32 to ensure the number has 4 bytes

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


    // Networking slots
    // TODO: Separate class ?
    void onNetworkErrorOccurred(QAbstractSocket::SocketError socketError);
    void onMessageIncoming();
    void onTestNetworkButtonClick();

    // Testing
    void onWriteDataButtonClick();



signals:
    void mainWindowResized(QResizeEvent *);
    void gamePhaseChanged(const GamePhases &newGamePhase);
    void turnEnded();
    void cardAddedToScene(Card &targetCard);
    void gameEndedAfterBattle(Player &loser);
};






#endif // GAME_H
