#ifndef BOTPLAYER_H
#define BOTPLAYER_H
#include "headers/Player.h"
#include <random>
class BotPlayer : public Player {
public:
  BotPlayer();
  BotPlayer(std::string, int points = 8000);
  //    ~BotPlayer();
private:
  bool decideToPlay();
  int randomGenerator(const int limit) const;
};

#endif // BOTPLAYER_H
