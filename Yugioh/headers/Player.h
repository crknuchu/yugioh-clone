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
  Player(std::string playerName, int points = 4000) : m_name(playerName), m_points(points){};

  //TODO 
  //implement deck


  //implement hand cards

  //implement graveyard

  std::string getPlayerName() const;
  unsigned getPlayerHealthPoints() const;
  void setPlayerHealthPoints(unsigned);

  void drawCards(unsigned int numOfCards);

  bool operator==(const Player &other) const; // a == b // In our case, a == *this, b == other

private:
    std::string m_name;
    unsigned m_points;
};

// std::istream &operator>>(std::istream &in, Player &p);
std::ostream &operator<<(std::ostream &out, Player &p);
#endif
