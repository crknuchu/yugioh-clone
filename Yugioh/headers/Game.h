#ifndef GAME_H
#define GAME_H

#include "Card.h"
#include "GamePhase.h"
#include "Player.h"
#include "Zone.h"

#include <QGraphicsScene>
#include <QMainWindow>
#include <QResizeEvent>
#include <QTcpSocket>

namespace Ui {
class MainWindow;
}

namespace GameExternVars {
extern Player* pCurrentPlayer;
extern Player* pOtherPlayer;
extern Card* pCardToBePlacedOnField;
extern Card* pAttackingMonster;
extern qint32 currentTurnClientID;
extern std::vector<Card*> yugiCards;
extern std::vector<Card*> kaibaCards;
extern Card* pCardToBeReturned;
} // namespace GameExternVars

class Game : public QMainWindow {
  Q_OBJECT
  using DESERIALIZATION_MEMBER_FUNCTION_POINTER = void (Game::*)(QDataStream&);

public:
  Game();
  Game(Player p1, Player p2, int lifePoints, int numberOfCards, int timePerMove,
       QWidget* parent = nullptr);
  ~Game();
  int lifePoints;
  int numberOfCards;
  int timePerMove;
  QString deck;

  // Public member functions:
  GamePhases setGamePhase() const;

  int getLifePoints() const;
  void setLifePoints(int newLifePoints);

  int getNumberOfCards() const;
  void setNumberOfCards(int newNumberOfCards);

  int getTimePerMove() const;
  void setTimePerMove(int newTimePerMove);

private:
  Ui::MainWindow* ui;
  QGraphicsScene* scene;
  GamePhases m_phase;
  Player m_player1;
  Player m_player2;
  int m_currentTurn;
  int counter = 0;
  int resizeCount = 0;
  int m_viewAndSceneWidth;
  //  bool firstMove = true;

  // Private member functions:
  int randomGenerator(const int limit) const;
  int decideWhoPlaysFirst() const;
  void firstTurnSetup(qint32 firstToPlay, qint32 clientID, float, float);
  void switchPlayers();

  void damageCalculation(Card* attackingMonster, Card* attackedMonster);
  void battleBetweenTwoAttackPositionMonsters(MonsterCard& attacker, MonsterCard& defender);
  void battleBetweenTwoDifferentPositionMonsters(MonsterCard& attacker, MonsterCard& defender);
  void damagePlayer(Player& targetPlayer, int howMuch);
  void visuallySetMonster(MonsterCard* monsterCard);
  void visuallySetSpell(SpellCard* spellCard);
  void visuallySetTrap(TrapCard* trapCard);
  void visuallyFlipMonster(MonsterCard* monsterCard, qreal degrees);
  void visuallyFlipSpell(SpellCard* spellCard);
  void visuallyFlipTrap(TrapCard* trapCard);

  Card* reconstructCard(QString cardName);
  qint32 findZoneNumber(Card& targetCard, Player* pWhoOwnsIt);
  Zone* findZone(qint32 zoneNumber, QString cardType, Player* pTargetPlayer);

  // QT related stuff:
  int m_windowWidth;
  int m_windowHeight;

  void setupConnections();
  bool eventFilter(QObject* obj, QEvent* event) override;

  // Networking:
  // TODO: Separate class?
  QTcpSocket* m_pTcpSocket = nullptr; // TODO: This will probably have to be in GameExternVars so
                                      // that EffectActivator can see it
  qint32 m_clientID;
  QString m_clientName;
  QDataStream m_inDataStream;
  QString m_currentHeader;
  static const std::map<QString, DESERIALIZATION_MEMBER_FUNCTION_POINTER> m_deserializationMap;

  bool sendDataToServer(QByteArray& data);
  void notifyServerThatDeserializationHasFinished();
  QByteArray QInt32ToQByteArray(qint32 source); // We use qint32 to ensure the number has 4 bytes

  void deserializeStartGame(QDataStream& deserializationStream);
  void deserializeFieldPlacement(QDataStream& deserializationStream);
  void deserializeAddCardToHand(QDataStream& deserializationStream);
  void deserializeLpChange(QDataStream& deserializationStream);
  void deserializeDeserializationFinished(QDataStream& deserializationStream);
  void deserializeGamePhaseChanged(QDataStream& deserializationStream);
  void deserializeNewTurn(QDataStream& deserializationStream);
  void deserializeEffectActivated(QDataStream& deserializationStream);
  void deserializeReposition(QDataStream& deserializationStream);
  void deserializeFlip(QDataStream& deserializationStream);
  void deserializeDestroyCard(QDataStream& deserializationStream);
  void deserializeGameEnd(QDataStream& deserializationStream);

private slots:
  void onGameStart(qint32 firstToPlay, qint32 clientID);
  void onBattlePhaseButtonClick();
  void onMainPhase2ButtonClick();
  void onEndPhaseButtonClick();
  void onMainWindowResize(QResizeEvent*);
  void onGamePhaseChange(const GamePhases& newGamePhase);
  void onTurnEnd();
  void onCardAddedToScene(Card* addedCard);
  void onActivateFromHand(Card&);

  // Slots for Card signal handling
  void onCardHoverEnter(Card&);
  void onCardHoverLeave(Card&);
  void onCardSelect(Card*);

  // Slots for CardMenu signal handling
  void onActivateButtonClick(Card& card);
  void onSetButtonClick(Card& card);
  void onSummonButtonClick(Card& card);
  void onAttackButtonClick(Card& card);
  void onRepositionButtonClick(Card& card);
  void onAttackDirectlyButtonClick(Card& card);
  void onFlipButtonClick(Card& card);

  // Slots for EffectActivator signal handling
  void onLifePointsChange(Player&);
  void onGameEnd(Player&); // const?
  void onMonsterReborn(Player&);
  void onChangeOfHeart(Player&, Player&);

  // Slots for Zone signal handling
  void onRedZoneClick(Zone* zone);
  void onGreenZoneClick(Zone* zone);
  void onBlueZoneClick(Zone* zone);

  void onReturnCardToOpponent();

  // Networking slots
  void onNetworkErrorOccurred(QAbstractSocket::SocketError socketError);
  void onDataIncoming();
  void onConnectButtonClick();

  // Testing
  void onWriteDataButtonClick();

signals:
  void returnCardToOpponent();
  void mainWindowResized(QResizeEvent*);
  void gameStarted(qint32 firstToPlay, qint32 clientID);
  void gamePhaseChanged(const GamePhases& newGamePhase);
  void turnEnded();
  void cardAddedToScene(Card* addedCard);
  void gameEndedAfterBattle(Player& loser);
  void lifePointsChanged(Player& targetPlayer);
  void deserializationFinished();
  void activateFromHand(Card&);
};

#endif // GAME_H
