#include "headers/CardList.h"

CardList::CardList(){};
CardList::CardList(std::vector<Card*> &cardList)
    :m_cardList(cardList){};
