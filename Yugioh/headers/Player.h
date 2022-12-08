#ifndef PLAYER_H
#define PLAYER_H

#include <string>
#include <iostream>
#include <memory>
#include "headers/Monstercard.h"
#include "headers/Spellcard.h"
#include "headers/Trapcard.h"
#include "headers/Game.h"
#include "Hand.h"

class Game;

class Player{ 

public:
  Player() = default;
  ~Player() {

  };
  Player(std::string playerName, int points = 8000) : m_name(playerName), m_points(points){};
  //DRAW PHASE
  void drawCards(unsigned int numOfCards);
  void activationSpellCard();
  void activationTrapCard();
  // ------------------------------------------

  //STANDBYPHASE
  void automaticallyActivationSBPhase();
  // ------------------------------------------

  //MAIN PHASE 1 
  Card &putCardOnTheTable(Hand &, Game &);
  void addMonsterCardOnTable(MonsterCard&);//activate this method whenever add new monsterCard on ground
  void automaticallyActivationMPhase();
  void setCardPosition();
  // ------------------------------------------

  //BATTLE PHASE
  int checkOpponentGround(const Player &opponent) const;
  std::vector<MonsterCard *> tableMonsterCards(const Player &opponent); //check vector size before attack
  void attackOpponent(Game &game, MonsterCard a, Player &opponent);

  // -----------------------------------------

  //MAIN PHASE 2 -> same as MAIN PHASE 1 + XYZ Summon
  void XYZSummon();
  // -----------------------------------------

  //END PHASE

  //TODO
  // add missing methods
  
  //


  std::string getPlayerName() const;
  unsigned getPlayerPoints();
  void setPoints(unsigned points);
  bool operator==(const Player &other) const; // a == b // In our case, a == *this, b == other
private:
    std::string m_name;
    unsigned m_points;
    std::vector<MonsterCard *> m_tableMonsterCards; //vector of monsterCards on the table, so i can check if opponent has any monsterCard on the table in order to attack him
    std::vector<SpellCard *>m_tableSpellCards;//live spell cards
    std::vector<TrapCard *>m_tableTrapCards;//live trap cards
};

// std::istream &operator>>(std::istream &in, Player &p);
std::ostream &operator<<(std::ostream &out, Player &p);
#endif
