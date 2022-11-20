#include "headers/Player.h"
#include <iostream>
#include <string>
#include <ostream>
#include <istream>
#include "headers/Card.h"
#include "headers/Hand.h"
#include <vector>
#include "headers/Monstercard.h"
std::string Player::getPlayerName() const{
    return this->m_name;
}

unsigned Player::getPlayerPoints(){
    return this->m_points;
}

void Player::setPoints(unsigned points){
    this->m_points+= points;
}


void Player::drawCards(unsigned int numOfCards) {

  std::cout << "The player " << this->getPlayerName() << " gets " << numOfCards << " cards." << std::endl;
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
    return out << "Player name: " << p.getPlayerName() << ", points " << p.getPlayerPoints()<<std::endl;
}

Card &Player::pickCardFromHand(){

    Card firstCard("first card", CardType::MONSTER_CARD, CardLocation::HAND, "do nothing");
    Card secondCard("second card", CardType::SPELL_CARD, CardLocation::HAND, "do nothing");
    std::vector<Card *> listOfCards;
    listOfCards.push_back(&firstCard);
    listOfCards.push_back(&secondCard);
    

    //need to implement mouse card pick event, now it just returns first card 
    if (listOfCards.size() == 0){
        std::cerr<<"empty hand";
        exit(EXIT_FAILURE);
    }else{
        return *listOfCards[0];
    }
}

int Player::checkOpponentGround(const Player &opponent) const {
    return 0;
}
void Player::attackOpponent(MonsterCard m, Player &opponent){

    // getCardType need to be refactorized, to return enum class of CardType, not a string
    if (m.getCardType() == CardType::MONSTER_CARD){
        if (0 == checkOpponentGround(opponent)){
            opponent.setPoints(-m.getAttackPoints());
        };
    }

}

