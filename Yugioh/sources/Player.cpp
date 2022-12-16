#include "headers/Player.h"

Player::Player(){}

Player::Player(std::string playerName, int points)
    : graveyard(Graveyard()), monsterZone(MonsterZone()),
      spellTrapZone(SpellTrapZone()), hand(Hand()), deck(Deck()),
      m_name(playerName), m_points(points){};

Player::~Player()
{
    std::cout << "We are in Player destructor because of player " << this->getPlayerName() << std::endl;
}



std::string Player::getPlayerName() const{
    return this->m_name;
}

unsigned Player::getPlayerLifePoints() const {
    return this->m_points;
}

void Player::setPlayerLifePoints(unsigned newHealthPoints)
{
    m_points = newHealthPoints;
}

void Player::drawCards(unsigned int numOfCards) {

    std::cout << "The player " << this->getPlayerName() << " gets " << numOfCards << " cards." << std::endl;

//    // Check if there are that many cards left in the deck
//    if(deck.getDeck().size() < numOfCards)
//        emit gameEndedNoCardsLeft(*this);

//    for(unsigned int i = 0; i < numOfCards;  i++)
//        hand.addToHand(*deck.draw());
}


// Operator overloads:
bool Player::operator==(const Player &other) const {
    return this->getPlayerName() == other.getPlayerName();
}

std::ostream &operator<<(std::ostream &out, Player &p){
    return out << "Player name: " << p.getPlayerName() << ", points " << p.getPlayerLifePoints()<<std::endl;
}





int Player::checkOpponentGround(Player &opponent) const {
    // return opponent.m_tableMonsterCards.getMonsterZone().size();
}
void Player::attackOpponent(Game &game, MonsterCard m, Player &opponent){

    // if (game.getGamePhase() == GamePhases::BATTLE_PHASE){   
    //     if (m.getCardType() == CardType::MONSTER_CARD){
    //         if (0 == checkOpponentGround(opponent)){
    //             opponent.setPlayerLifePoints(m.getAttackPoints());
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

