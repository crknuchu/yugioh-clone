#ifndef GAME_H
#define GAME_H

#include "Player.h"
#include <QGraphicsView>

class Game: public QGraphicsView
{
public:
  Game();
  Game(Player p1, Player p2);
  ~Game();

  // Public member functions:
  void start();

private:
  QGraphicsScene *scene;

  Player m_player1;
  Player m_player2;
  Player *m_pCurrentPlayer;
  Player *m_pOtherPlayer;

  int m_turnNumber;

  // Private member functions:
  int randomGenerator(const int limit) const;
  int decideWhoPlaysFirst() const;
  void firstTurnSetup();
  void switchPlayers();
};






#endif // GAME_H
