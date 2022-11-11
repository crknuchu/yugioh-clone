// Placeholder Player.cpp, subject to change
#include "headers/Player.h"
#include <iostream>


Player::Player(){}
Player::Player(std::string name)
  :m_name(name) {}
Player::~Player(){}

std::string Player::getName() {
    return m_name;
}

void Player::drawCards(int n) {

  std::cout << "The player " << this->getName() << " gets " << n << " cards." << std::endl;
}



