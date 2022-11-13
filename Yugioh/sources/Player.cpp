// Placeholder Player.cpp, subject to change
#include "headers/Player.h"
#include <iostream>


Player::Player(){}
Player::Player(std::string name)
  :m_name(name) {}
Player::~Player(){}

std::string Player::getName() const {
    return m_name;
}

void Player::drawCards(int n) {

  std::cout << "The player " << this->getName() << " gets " << n << " cards." << std::endl;
}




// Operator overloads:
bool Player::operator==(const Player &other) const {
    return this->getName() == other.getName();
}



