#ifndef PLAYER_H
#define PLAYER_H

#include <string>
#include <iostream>
#include <memory>
#include <ostream>
#include <istream>
#include <vector>
#include "Monstercard.h"
#include "Monstercard.h"
#include "SpellTrapZone.h"
#include "Hand.h"
#include "Deck.h"
#include "Card.h"
#include "Graveyard.h"
#include "MonsterZone.h"
#include "SpellTrapZone.h"
#include "GamePhase.h"

#include "Hand.h"
#include "Deck.h"

#include "Graveyard.h"
#include "MonsterZone.h"
#include "SpellTrapZone.h"



class Player{ 

public:
  Player();
  Player(std::string playerName,int points = 8000);
  ~Player();


  std::string getPlayerName() const;
  unsigned getPlayerLifePoints() const;

  void setPoints(unsigned points);

  void drawCards(unsigned int numOfCards);

  void setPlayerLifePoints(unsigned points);

  Graveyard graveyard;
  MonsterZone monsterZone;
  SpellTrapZone spellTrapZone;
  Hand hand;
  Deck deck;

  bool operator==(const Player &other) const; // a == b // In our case, a == *this, b == other


private:
    std::string m_name;
    unsigned m_points;

};

// std::istream &operator>>(std::istream &in, Player &p);
std::ostream &operator<<(std::ostream &out, Player &p);
#endif
