#include "headers/Player.h"
#include "headers/GamePhase.h"
Player::Player(){}

Player::Player(std::string playerName, int points) : graveyard(Graveyard()),
    monsterZone(MonsterZone()), spellTrapZone(SpellTrapZone()), hand(Hand()),
    deck(Deck()) , m_name(playerName), m_points(points){};

Player::Player(Player &p){
    this->spellTrapZone = p.spellTrapZone;
    this->monsterZone = p.monsterZone;
    this->deck = p.deck;
    this->graveyard = p.graveyard;
    this->hand = p.hand;
    this->m_points = p.m_points;
    this->m_name = p.m_name;

}

Player Player::operator=(Player &p){
    return p;
}

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

void Player::setDeck(Deck &d) {
    this->deck = d;
}

//DRAW PHASE 

void Player::drawCards(unsigned int numOfCards) {
    //TODO refactor
    std::vector<Card *>currentDeck = this->deck.getDeck();
    unsigned int deckSize = currentDeck.size();
    std::cout<<"num of card " << deckSize << std::endl;
    if (this->deck.getDeck().empty() == true || deckSize < numOfCards)
    {
        std::cout<<this->getPlayerName() << " cant draw cards" << std::endl;
        return;
    }
    else{
        std::vector<Card*> newCards = this->deck.draw(numOfCards);
        for (unsigned i = 0; i < newCards.size(); i++){
            this->hand.addToHand(*newCards[i]);
        }
        std::cout << "The player " << this->getPlayerName() << " gets " << newCards.size() << " cards." << std::endl;
    }
}

void Player::drawCards(){

    Player::drawCards(1);
}

// ---------------------------------------------


// STANDBY PHASE
void Player::activationSpellTrapCard(Card &card){
    //TODO

    std::cout<<card.getCardName() << " is activated " << std::endl;
    SpellCard *tmp = dynamic_cast<SpellCard *>(&card);
    if (tmp != nullptr){
        // effectActivator function() for spell card;
        delete tmp;
        return;
    }
    else {
        TrapCard *tmp = dynamic_cast<TrapCard*>(&card);
        tmp = dynamic_cast<TrapCard *>(&card);
        if (tmp != nullptr){
            //effectActivator funciton() for trap card;
        }
        delete tmp;
    }
}
// --------------------------------------------

// BATTLE PHASE

int Player::checkOpponentGround(Player &opponent) {
       std::vector<Zone*>cards = opponent.monsterZone.m_monsterZone; //first monsterZone is field in player.h
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


