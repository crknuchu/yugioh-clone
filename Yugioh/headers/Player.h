#ifndef PLAYER_H
#define PLAYER_H

#include <string>
#include <iostream>
#include <memory>

class Player{ 

public:
  Player() = default;
  ~Player() {

  };
  Player(std::string playerName, int points = 8000) : m_name(playerName), m_points(points){};

  Card &pickCardFromHand();
  void drawCards(unsigned int numOfCards);
  void attackOpponent(MonsterCard a, Player &opponent);
  std::string getPlayerName() const;
  unsigned getPlayerPoints();
  void setPoints(unsigned points);
  bool operator==(const Player &other) const; // a == b // In our case, a == *this, b == other
  int checkOpponentGround(const Player &opponent) const;
private:
    std::string m_name;
    unsigned m_points;
};

// std::istream &operator>>(std::istream &in, Player &p);
std::ostream &operator<<(std::ostream &out, Player &p);
#endif
