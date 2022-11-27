#include "headers/Player.h"
#include <iostream>
#include <string>
#include <ostream>
#include <istream>
#include "headers/Card.h"
#include "headers/Game.h"
#include "headers/Hand.h"
#include "headers/CardList.h"
#include <vector>
#include "headers/Monstercard.h"
std::string Player::getPlayerName() const{
    return this->m_name;
}

unsigned Player::getPlayerPoints(){
    return this->m_points;
}

void Player::setPoints(unsigned points){
    this->m_points-= points;
}


void Player::drawCards(unsigned int numOfCards) {
    //TODO
    //draw cards only if game is in draw phase
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

GamePhase Player::getGamePhase(const GamePhase &a) const{
    
    if (a == GamePhase::DRAW_PHASE){
        return GamePhase::DRAW_PHASE;
    }
    if (a == GamePhase::STANDBY_PHASE){
        return GamePhase::STANDBY_PHASE;
    }
    if (a == GamePhase::MAIN_PHASE_1){
        return GamePhase::MAIN_PHASE_1;
    }
    if (a == GamePhase::BATTLE_PHASE){
        return GamePhase::BATTLE_PHASE;
    }
    if (a == GamePhase::MAIN_PHASE_2){
        return GamePhase::MAIN_PHASE_2;
    }
    else {
        return GamePhase::END_PHASE;
    }
}


Card &Player::putCardOnTheTable(Hand &hand, const GamePhase &phase){

    std::vector<Card *> tmp_hand = hand.getHand();

    //if player doesn't have any card in hand, he lose game 
    if (tmp_hand.empty()){
        this->setPoints(this->getPlayerPoints());
        throw "GAME ENDED\n";
    }

    //need to implement mouse card pick event, now it just returns first card 
    GamePhase tmpPhase = getGamePhase(phase);
    if (tmpPhase == GamePhase::MAIN_PHASE_1 || tmpPhase == GamePhase::MAIN_PHASE_2){
        //TODO 
        //pickCard from hand, remove from it, and put on the table

        return *tmp_hand[0];
    }
    else 
        throw "Incompatibile game phase\n";

}

int Player::checkOpponentGround(const Player &opponent) const {
    //TODO
    //implement ground.h ground.cpp
    return 0;
}
void Player::attackOpponent(const GamePhase &game, MonsterCard m, Player &opponent){

    if (getGamePhase(game) == GamePhase::BATTLE_PHASE){   
        if (m.getCardType() == CardType::MONSTER_CARD){
            if (0 == checkOpponentGround(opponent)){
                opponent.setPoints(m.getAttackPoints());
            }
        }
        else {
            //TODO
            //pick opponent card to fight()
        }
    }
    else {
        std::cerr<<"incompatibile game phase, can't attack at this moment"<<std::endl;
    }

}

