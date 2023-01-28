#include "headers/CardList.h"

CardList::CardList() = default;
;
CardList::CardList(std::vector<Card*>& cardList) : m_cardList(cardList){};
