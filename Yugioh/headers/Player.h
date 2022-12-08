#ifndef PLAYER_H
#define PLAYER_H

#include <string>
#include <iostream>
#include <memory>
#include <ostream>
#include <istream>
#include <vector>
#include "headers/Monstercard.h"
#include "headers/Spellcard.h"
#include "Monstercard.h"
#include "SpellTrapZone.h"
#include "headers/Trapcard.h"
#include "headers/Game.h"
#include "Hand.h"
#include "Deck.h"
#include "Card.h"
#include "Graveyard.h"
#include "MonsterZone.h"
#include "headers/CardList.h"
#include "SpellTrapZone.h"

class Game;

class Player{ 

public:
  Player();
  ~Player() {

  };
  Player(std::string playerName, Deck &deck, Hand &hand, Graveyard &grave,int points = 8000) : m_name(playerName), m_points(points), m_deck(deck), m_hand(hand), m_graveyard(grave){};
  //DRAW PHASE
  void drawCards(unsigned int numOfCards); //done
  void activationSpellCard(Card &); 
  void activationTrapCard(Card &);
  // ------------------------------------------

  //STANDBYPHASE
  void automaticallyActivationSBPhase(); //stanby phase
  // ------------------------------------------

  //MAIN PHASE 1 
  Card &putCardOnTheTable(Hand &, Game &);
  void addMonsterCardOnTable(MonsterCard&);//activate this method whenever add new monsterCard on ground
  void automaticallyActivationMPhase(); // mainPhase
  void setCardPosition();
  // ------------------------------------------

  //BATTLE PHASE
  int checkOpponentGround(Player &opponent) const;
  // std::vector<MonsterCard *> tableMonsterCards(const Player &opponent); //check vector size before attack
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
    Hand m_hand;
    Deck m_deck;
    std::string m_name;
    unsigned m_points;
    Graveyard m_graveyard;
    MonsterZone m_tableMonsterCards; 
    SpellTrapZone m_tableTrapSepllCards;
};

// std::istream &operator>>(std::istream &in, Player &p);
std::ostream &operator<<(std::ostream &out, Player &p);
#endif
