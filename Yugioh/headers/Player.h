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

#include "Graveyard.h"
#include "MonsterZone.h"
#include "SpellTrapZone.h"


class Player{ 

public:
  Player();
  ~Player() {

  };
  Player(std::string playerName,int points = 8000) : m_graveyard(Graveyard()),
      m_monsterZone(MonsterZone()), m_SpellTrapZone(SpellTrapZone()), m_hand(Hand()),
      m_deck(Deck()) , m_name(playerName), m_points(points){};
  //DRAW PHASE
  void drawCards(unsigned int numOfCards); //done
  void drawCards();
  // ------------------------------------------

  //STANDBYPHASE
  void activationSpellTrapCard(Card &); // need emit signal that send reference to card which needs to be activated

  // ----------------------------------------------------------------------------------------------------------------
  //THESE FUNCTIONS DONT NEED TO BE IMPLEMENTED - FUNCTION ABOVE WILL DO THAT EFFECT INSTEAD, JUST BEFORE ACTIVATION|
  // NEED TO CHECK GAME PHASE                                                                                       |
  //   void automaticallyActivationSBPhase(); // not necessary, function above will do the same thing               |
  //   void automaticallyActivationMPhase(); //                                                                     |
  // ----------------------------------------------------------------------------------------------------------------

  //MAIN PHASE 1 
  void setCardPosition();
  // ------------------------------------------

  //BATTLE PHASE
  int checkOpponentGround(Player &opponent);
  // std::vector<MonsterCard *> tableMonsterCards(const Player &opponent); //check vector size before attack
  void attackOpponent(MonsterCard a, Player &opponent);

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
  Graveyard m_graveyard;
  MonsterZone m_monsterZone;
  SpellTrapZone m_SpellTrapZone;
  Hand m_hand;
  Deck m_deck;
  unsigned doDirectDamage(unsigned);
  void addPoints(unsigned);
  void setDeck(Deck &);
private:
    std::string m_name;
    unsigned m_points;
};

// std::istream &operator>>(std::istream &in, Player &p);
std::ostream &operator<<(std::ostream &out, Player &p);
#endif
