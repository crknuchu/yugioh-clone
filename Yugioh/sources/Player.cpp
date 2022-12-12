#include "headers/Player.h"
#include <iostream>
#include <string>
#include <ostream>
#include <istream>

Player::Player(){}

Player::Player(std::string playerName, int points)
    : graveyard(Graveyard()), monsterZone(MonsterZone()),
      spellTrapZone(SpellTrapZone()), hand(Hand()),
      deck(Deck()) , m_name(playerName), m_points(points)
{}

Player::~Player(){}


std::string Player::getPlayerName() const{
    return this->m_name;
}

unsigned Player::getPlayerPoints(){
    return this->m_points;
}

void Player::setPoints(unsigned points) {
    this->m_points = points;
}

void Player::drawCards(unsigned int numOfCards) {

  std::cout << "The player " << this->getPlayerName() << " gets " << numOfCards << " cards." << std::endl;
}

// Operator overloads:
bool Player::operator==(const Player &other) const {
    return this->getPlayerName() == other.getPlayerName();
}

std::ostream &operator<<(std::ostream &out, Player &p){
    return out << "Player name: " << p.getPlayerName() << ", points " << p.getPlayerPoints()<<std::endl;
}
