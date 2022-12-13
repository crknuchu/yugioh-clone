#include "headers/Player.h"
#include "headers/GamePhase.h"
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
    std::cout<<"num of card " << this->m_deck.getDeck().size()<<std::endl;
//    try{
//        if (this->m_deck.getDeck().size() <= 0){
//            throw "Empty deck, player lost!\n";
//        }
//        else {
//            std::vector<Card*> newCards = this->m_deck.draw(numOfCards);
//            for (unsigned i = 0; i < newCards.size(); i++){
//                this->m_hand.addToHand(*newCards[i]);
//            }
//            std::cout << "The player " << this->getPlayerName() << " gets " << newCards.size() << " cards." << std::endl;
//        }
//    }
//    catch (std::exception err){
//        throw "error";
//    }
}
void Player::activationSpellCard(){
  //TODO
//    std::vector<Card*> currentCards = this->m_SpellTrapZone;
//    for (unsigned i = 0; i < currentCards.size(); i++){
//        // if (makeActivationDecision(currentCards[i]) == true)-> return true if player decided to activate this card
//        //      summoningCards(currentCards[i]) -> from effectACtivator class fetch method
//                std::cout<<currentCards[i]->getCardName() <<" has been activated\n";
//    }
}

void Player::activationTrapCard(){
  //TODO
//    std::vector<Card*> currentCards = this->m_SpellTrapZone.getSpellTrapZone();
//    for (unsigned i = 0; i < currentCards.size(); i++){
//        // if (makeActivationDecision(currentCards[i]) == true)-> return true if player decided to activate this card
//        //      summoningCards(currentCards[i]) -> from effectActivator class fetch method
//                std::cout<<currentCards[i]->getCardName() <<" has been activated\n";
//    }
}

// ---------------------------------------------


// STANDBY PHASE
void Player::automaticallyActivationSBPhase(){

}

// --------------------------------------------

// BATTLE PHASE

int Player::checkOpponentGround(Player &opponent) {
//    return opponent.m_monsterZone.getMonsterZone().size();
}

void Player::attackOpponent(MonsterCard a, Player &opponent){

    GamePhasesEnum tmpPhase = GamePhase::currentGamePhase;
    if (tmpPhase == GamePhasesEnum::BATTLE_PHASE){
        if (checkOpponentGround(opponent) == 0){
            opponent.setPoints(a.getAttackPoints());
        }
        else {
            std::cout<<"decide what card do u want to attack, attack points of " << a.getCardName()<< " is " << a.getAttackPoints() << std::endl;
            //TODO
            // implement opponent card for attack
        }
    }
    else {
        std::cerr<<"not a battle phase, can't attack now\n"<<std::endl;
    }
}

// --------------------------------------------
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


