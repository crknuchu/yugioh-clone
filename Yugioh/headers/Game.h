#ifndef GAME_H
#define GAME_H

#include "Player.h"

class Game
{
public:
  Game();
  Game(Player p1, Player p2);
  ~Game();

  // Public member functions:
  void start();

private:
  Player m_p1;
  Player m_p2;
  int m_first;  // The number of the player who plays first // TODO: Maybe m_current instead of m_first for reusability
  int m_turnNumber;

  // Private member functions:
  int randomGenerator(const int limit);
  int decideWhoPlaysFirst();
  void firstTurnSetup();
};






#endif // GAME_H
