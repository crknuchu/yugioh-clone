#include "headers/Player.h"
#include <iostream>
#include <string>
#include <ostream>
#include <istream>


std::string Player::get_player_name(){
    return this->name;
}

unsigned Player::get_player_points(){
    return this->points;
}

void Player::drawCards(int n) {

  std::cout << "The player " << this->getName() << " gets " << n << " cards." << std::endl;
}

// Operator overloads:
bool Player::operator==(const Player &other) const {
    return this->getName() == other.getName();
}

// std::istream &operator>>(std::istream &in, Player &p){
//     char c; //for space/comma reading
//     in >>  >> c >> p.points;
//     return in;
// }

std::ostream &operator<<(std::ostream &out, Player &p){
    return out << "Player name: " << p.get_player_name() << ", points " << p.get_player_points()<<std::endl; 
}
