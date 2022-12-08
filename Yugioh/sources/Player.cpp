#include "headers/Player.h"
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
    //TODO
    if (this->m_deck.getDeck().size() < numOfCards){
        this->setPoints(0);
        throw "Can't draw anymore, GAME ENDED!";
    }
    std::vector<Card *> new_cards = this->m_deck.draw(numOfCards);
    for (int i = 0; i < new_cards.size(); i++){
        this->m_hand.addToHand(*new_cards[i]);
    }
    //draw cards only if game is in draw phase
  std::cout << "The player " << this->getPlayerName() << " gets " << numOfCards << " cards." << std::endl;
}

void Player::activationSpellCard(Card &spellCard){ 
    //need activation first
    if (spellCard.getCardType() == CardType::SPELL_CARD){

    this->m_graveyard.sendToGraveyard(spellCard);
    }
    else
        throw "NOT A SPELL CARD\n";
}

// ---------------------------------------------


// STANDBY PHASE

void Player::automaticallyActivationSBPhase() {
    std::vector<Card *>array = this->m_tableTrapSepllCards.getSpellTrapZone();
    for (int i = 0 ; i < array.size(); i++){
        if (array[i]->getCardName() == "Treeborn Frog")
        {
        //activate;
        }
    }

}
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



Card &Player::putCardOnTheTable(Hand &hand, Game &game){

    std::vector<Card *> tmp_hand = hand.getHand();

    //if player doesn't have any card in hand, he lose game 
    if (tmp_hand.empty()){
        this->setPoints(this->getPlayerPoints());
        throw "GAME ENDED\n";
    }

    //need to implement mouse card pick event, now it just returns first card 
    GamePhases tmpPhase = game.getGamePhase();
    if (tmpPhase == GamePhases::MAIN_PHASE1 || tmpPhase == GamePhases::MAIN_PHASE2){
        //TODO 
        //pickCard from hand, remove from it, and put on the table

        return *tmp_hand[0];
    }
    else 
        throw "Incompatibile game phase\n";

}

int Player::checkOpponentGround(Player &opponent) const {
    return opponent.m_tableMonsterCards.getMonsterZone().size();
}
void Player::attackOpponent(Game &game, MonsterCard m, Player &opponent){

    if (game.getGamePhase() == GamePhases::BATTLE_PHASE){   
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

void Player::addMonsterCardOnTable(MonsterCard &card){

    
    if (card.getCardType() == CardType::MONSTER_CARD){
        this->m_tableMonsterCards.getMonsterZone().push_back(&card);
        return;
    }
    else
    {
        throw "Not a monsterCard, cannot add to monsterCard vector\n";
    }

}
