#ifndef PLAYER_H
#define PLAYER_H

#include <string>
#include <iostream>
#include <memory>
#include "headers/Monstercard.h"
#include "headers/Game.h"
#include "Hand.h"

class Game;

class Player{ 

public:
  Player() = default;
  ~Player() {

  };
  Player(std::string playerName, int points = 8000) : m_name(playerName), m_points(points){};

  Card &putCardOnTheTable(Hand &, Game &);
  void drawCards(unsigned int numOfCards);
  void attackOpponent(Game &game, MonsterCard a, Player &opponent);
  std::string getPlayerName() const;
  unsigned getPlayerPoints();
  void setPoints(unsigned points);
  bool operator==(const Player &other) const; // a == b // In our case, a == *this, b == other
  int checkOpponentGround(const Player &opponent) const;
  void addMonsterCardOnTable(MonsterCard&);//activate this method whenever add new monsterCard on ground
  std::vector<MonsterCard *> tableMonsterCards(const Player &opponent); //check vector size before attack
private:
    std::string m_name;
    unsigned m_points;
    std::vector<MonsterCard *> m_tableMonsterCards; //vector of monsterCards on the table, so i can check if opponent has any monsterCard on the table in order to attack him
};

// std::istream &operator>>(std::istream &in, Player &p);
std::ostream &operator<<(std::ostream &out, Player &p);
#endif
