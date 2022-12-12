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

class Player{ 

public:
  Player();
  ~Player() {

  };
  Player(std::string playerName,int points = 8000) : m_graveyard(Graveyard()), m_monsterZone(MonsterZone()), m_SpellTrapZone(SpellTrapZone()), m_hand(Hand()), m_deck(Deck()) , m_name(playerName), m_points(points){};
  //DRAW PHASE
  void drawCards(unsigned int numOfCards); //done
  void activationSpellCard(Card &); 
  void activationTrapCard(Card &);
  // ------------------------------------------

  //STANDBYPHASE
  void automaticallyActivationSBPhase(); //stanby phase
  // ------------------------------------------

  //MAIN PHASE 1 
  void automaticallyActivationMPhase(); // mainPhase
  void setCardPosition();
  // ------------------------------------------

  //BATTLE PHASE
  int checkOpponentGround(Player &opponent) const;
  // std::vector<MonsterCard *> tableMonsterCards(const Player &opponent); //check vector size before attack
  void attackOpponent(Game &game, MonsterCard a, Player &opponent);

  // -----------------------------------------

  std::string getPlayerName() const;
  unsigned getPlayerLifePoints() const;
  void setPlayerLifePoints(unsigned points);
  bool operator==(const Player &other) const; // a == b // In our case, a == *this, b == other
  Graveyard m_graveyard;
  MonsterZone m_monsterZone;
  SpellTrapZone m_SpellTrapZone;
  Hand m_hand;
  Deck m_deck;
private:
    std::string m_name;
    unsigned m_points;
};

// std::istream &operator>>(std::istream &in, Player &p);
std::ostream &operator<<(std::ostream &out, Player &p);
#endif
