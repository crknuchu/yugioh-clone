#ifndef DECK_H
#define DECK_H

#include "CardList.h"
#include <string>

class Deck : public CardList {
public:
  Deck();
  Deck(std::vector<Card *> &);
  void setDeck(float, float, int);
  std::vector<Card *> getDeck() const;
  Card *draw();
  std::vector<Card *> draw(int numberOfCards);
  void shuffleDeck(unsigned seed);

  std::vector<Card *> uiDeck;
};

#endif // DECK_H
