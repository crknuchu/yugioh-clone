#include "headers/Card.h"
#include "headers/Hand.h"
#include "headers/Deck.h"
#include "headers/Graveyard.h"
#include <iostream>

int main()
{
    Card card1 = Card("plavac", "plavi zmaj");
    Card card2 = Card("zmaj", "crni zmaj");
    Card card3 = Card("okut", "beli zmaj");
    std::vector<Card> c;
//    c.push_back(card1);
//    c.push_back(card2);
//    c.push_back(card1);
//    std::cout << "hand:" << std::endl;
//    Hand h = Hand(c);
//    std::cout << "deck:" << std::endl;
//    c.push_back(card3);
//    c.push_back(card3);
//    Deck d = Deck("hello",c);

//    std::cout << "grave:" << std::endl;
    Graveyard g = Graveyard(c);
//    std::vector<Card> d_copy = d.getDeck();
//    std::vector<Card> drawnCards = d.draw(2);

//    d.shuffleDeck();
    g.sendToGraveyard(card1);
    g.sendToGraveyard(card2);

    std::optional<Card> cardFromGY  = g.removeFromGraveyard(card1);
    std::cout << cardFromGY->name();
}
