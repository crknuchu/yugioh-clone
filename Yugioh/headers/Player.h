#ifndef PLAYER_H
#define PLAYER_H

#include <string>
#include <iostream>
#include <memory>
#include <ostream>
#include <istream>
#include <vector>
#include <QObject>
#include "Monstercard.h"
#include "Monstercard.h"
//#include "SpellTrapZone.h"
#include "Hand.h"
#include "Deck.h"

//#include "Graveyard.h"
//#include "MonsterZone.h"
//#include "SpellTrapZone.h"
#include "Field.h"

class Player : public QObject {
    Q_OBJECT
public:
  Player();
  Player(Player &);
  ~Player(){};
  Player operator=(Player &);
  Player(std::string playerName,int points = 8000);
  //DRAW PHASE
  void drawCards(unsigned int numOfCards); //done
  void drawCards();
  // ------------------------------------------


  void setCardPosition(); // don't need to do it
  void putCardOnField(Card &); //same as above
  // ------------------------------------------

  //BATTLE PHASE
  int checkOpponentGround(Player &opponent);
  void sendToGraveyard(Card &);
  void sendToGraveyard(Card &, Zone *);
  void discard(Card &);

  void fromGraveyardToHand(Card &);
  void fromGraveyardToField(Card &, int);



  bool isCardInGrave(Card &c);


  std::string getPlayerName() const;
  unsigned getPlayerLifePoints() const;
  void setPlayerLifePoints(unsigned points);
  bool operator==(const Player &other) const; // a == b // In our case, a == *this, b == other

  std::vector<Card *>drawenCards(unsigned int num);
//  void setPlayerLifePoints(unsigned);
  void setPoints(unsigned);
  unsigned doDirectDamage(unsigned);
  void addPoints(unsigned);
  void setDeck(Deck &);
  Hand m_hand;
  Field field;

signals:
  void cardAddedToScene(Card *);
private:
    std::string m_name;
    unsigned m_points;

signals:
    void cardDrawn(Card *pDrawnCard);
};

// std::istream &operator>>(std::istream &in, Player &p);
std::ostream &operator<<(std::ostream &out, Player &p);
#endif
