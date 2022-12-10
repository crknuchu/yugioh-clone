#include "headers/Player.h"
#include <iostream>
#include <string>
#include <ostream>
#include <istream>


std::string Player::getPlayerName() const{
    return this->m_name;
}



unsigned Player::getPlayerHealthPoints() const {
    return this->m_points;
}

void Player::setPlayerHealthPoints(unsigned newHealthPoints)
{
    m_points = newHealthPoints;
}

void Player::drawCards(unsigned int numOfCards) {

    std::cout << "The player " << this->getPlayerName() << " gets " << numOfCards << " cards." << std::endl;
}

void Player::changeHealthPointsBy(int pointsChange)
{
    unsigned newHealthPoints = this->getPlayerHealthPoints() + pointsChange;

    this->setPlayerHealthPoints(newHealthPoints);
}

// Operator overloads:
bool Player::operator==(const Player &other) const {
    return this->getPlayerName() == other.getPlayerName();
}

// std::istream &operator>>(std::istream &in, Player &p){
//     char c; //for space/comma reading
//     in >>  >> c >> p.points;
//     return in;
// }

std::ostream &operator<<(std::ostream &out, Player &p){
    return out << "Player name: " << p.getPlayerName() << ", points " << p.getPlayerHealthPoints()<<std::endl;
}
