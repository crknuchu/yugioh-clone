#include "headers/Player.h"

Player::Player(){}

std::string Player::getPlayerName() const{
    return this->m_name;
}

unsigned Player::getPlayerPoints(){
    return this->m_points;
}

void Player::setPoints(unsigned points){
    this->m_points-= points;
}

//DRAW PHASE 

void Player::drawCards(unsigned int numOfCards) {
    //TODO refactor
  std::cout << "The player " << this->getPlayerName() << " gets " << numOfCards << " cards." << std::endl;
}

void Player::activationSpellCard(Card &spellCard){ 
  //TODO
}

// ---------------------------------------------


// STANDBY PHASE


//


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





int Player::checkOpponentGround(Player &opponent) const {
    // return opponent.m_tableMonsterCards.getMonsterZone().size();
}
void Player::attackOpponent(Game &game, MonsterCard m, Player &opponent){

    // if (game.getGamePhase() == GamePhases::BATTLE_PHASE){   
    //     if (m.getCardType() == CardType::MONSTER_CARD){
    //         if (0 == checkOpponentGround(opponent)){
    //             opponent.setPoints(m.getAttackPoints());
    //         }
    //     }
    //     else {
    //         //TODO
    //         //pick opponent card to fight()
    //     }
    // }
    // else {
    //     std::cerr<<"incompatibile game phase, can't attack at this moment"<<std::endl;
    // }

}

