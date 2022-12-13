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
    this->m_points = points;
}

unsigned Player::doDirectDamage(unsigned points) {
    return this->m_points - points;
}

void Player::addPoints(unsigned points){
    this->m_points = this->m_points + points;
}

//DRAW PHASE 

void Player::drawCards(unsigned int numOfCards) {
    //TODO refactor
    std::vector<Card *>currentDeck = this->m_deck.getDeck();
    unsigned int deckSize = currentDeck.size();
    std::cout<<"num of card " << deckSize << std::endl;
    if (this->m_deck.getDeck().empty() == true || deckSize < numOfCards)
    {
        std::cout<<"cant draw cards\n";
        return;
    }
    else{
        std::vector<Card*> newCards = this->m_deck.draw(numOfCards);
        for (unsigned i = 0; i < newCards.size(); i++){
            this->m_hand.addToHand(*newCards[i]);
        }
        std::cout << "The player " << this->getPlayerName() << " gets " << newCards.size() << " cards." << std::endl;
    }
}
void Player::activationSpellTrapCard(){
  //TODO
//    std::vector<Card*> currentCards = this->m_SpellTrapZone;
    std::cout<<"You have " << this->m_SpellTrapZone.size()
            << " cards on the ground\nDo you want to activate some spell/trap card"<<std::endl;

//    for (unsigned i = 0; i < currentCards.size(); i++){
//        // if (makeActivationDecision(currentCards[i]) == true)-> return true if player decided to activate this card
//        //      summoningCards(currentCards[i]) -> from effectACtivator class fetch method
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
       std::vector<Zone*>cards = opponent.m_monsterZone.m_monsterZone; //first monsterZone is field in player.h
                                                                       //second one is filed in monsterZone.h
       return std::accumulate(cards.begin(), cards.end(), 0, [](unsigned acc, Zone *card){
           if (card->isEmpty() == false)
           {
               return acc;
           }
           else {
               return acc + 1;
           }
       });
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


