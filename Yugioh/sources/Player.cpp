#include "headers/Player.h"
#include "headers/GamePhase.h"
Player::Player(){}

Player::Player(std::string playerName, int points) : m_hand(Hand()), field(Field()), m_name(playerName), m_points(points){};


Player::Player(Player &p){
    this->field = p.field;
    this->m_points = p.m_points;
    this->m_name = p.m_name;

}

Player Player::operator=(Player &p){
    return p;
}

std::string Player::getPlayerName() const{
    return this->m_name;
}

unsigned Player::getPlayerLifePoints() const {
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
    this->field.deck = d;
}
void Player::setPlayerLifePoints(unsigned newHealthPoints)
{
    m_points = newHealthPoints;
}

void Player::drawCards(unsigned int numOfCards) {
    //TODO refactor
    std::vector<Card *>currentDeck = this->field.deck.getDeck();
    unsigned int deckSize = currentDeck.size();
    std::cout<<"num of card " << deckSize << std::endl;
    if (this->field.deck.getDeck().empty() == true || deckSize < numOfCards)
    {
        std::cout<<this->getPlayerName() << " cant draw cards" << std::endl;
        return;
    }
    else{
        std::vector<Card*> newCards = this->field.deck.draw(numOfCards);
        for (Card* newCard : newCards ){
            emit cardAddedToScene(newCard);
            this->m_hand.addToHand(*newCard);
        }
        std::cout << "The player " << this->getPlayerName() << " gets " << newCards.size() << " cards." << std::endl;
    }
}

void Player::drawCards(){

    Player::drawCards(1);
}

// ---------------------------------------------


void Player::fromGraveyardToHand(Card &card){

    for (auto it : this->field.graveyard->getGraveyard())
    {
        if ((*it) == card) {
            this->field.graveyard->removeFromGraveyard(card);
            this->m_hand.addToHand(card);
            return;
        }
    }

}

bool Player::isCardInGrave(Card &c)
{
    for (auto it : this->field.graveyard->getGraveyard())
    {
        if ((*it) == c)
        {
            return true;
        }
    }
    return false;
}


void Player::fromGraveyardToField(Card &card, int zoneNumber)
{
    if (isCardInGrave(card) == true)
    {
        this->field.graveyard->removeFromGraveyard(card); // this function return removed card,
                                                                // but in this case we dont need it
        //put it back in filed zone
        if (card.getCardType() == CardType::MONSTER_CARD)
        {
            this->field.monsterZone.colorFreeZones();
            this->field.monsterZone.placeInMonsterZone(&card, zoneNumber);
        }
        else if (card.getCardType() == CardType::SPELL_CARD || card.getCardType() == CardType::TRAP_CARD)
        {
            this->field.spellTrapZone.colorFreeZones();
            this->field.spellTrapZone.placeInSpellTrapZone(&card, zoneNumber);
        }
    }
    else
    {
        std::cerr<<card.getCardName()<<" not in graveyard"<<std::endl;
        return;
    }
}



void Player::sendToGraveyard(Card &card, Zone *zone)
{
      zone->m_pCard = nullptr; //free space for that zone, card is sent to graveyard ===> zone.isEmpty() returns true after
      this->field.graveyard->sendToGraveyard(card);

}

void Player::sendToGraveyard(Card &card){
    //first need to be removed from field
    try {
        //removing from deck, not sure if is it legal move

        for (auto it : this->m_hand.getHand()){
            if ((*it) == card){
               this->m_hand.removeFromHand(card);
               this->field.graveyard->sendToGraveyard(card);
               std::cout<< card.getCardName() << " succesfully removed from hand"<<std::endl;
               return;
            }
        }
   }
    catch(std::exception e){
       std::cerr<<card.getCardName()<<" can't be removed"<<std::endl;
//        throw e;
    }
}


void Player::discard(Card &card) {
    Card* removedCard = this->m_hand.removeFromHand(card);
    this->field.graveyard->sendToGraveyard(*removedCard);
}

// --------------------------------------------
std::vector<Card *> Player::drawenCards(unsigned int num)
{
    std::vector<Card*> cards = this->field.deck.getDeck();
    if (cards.size() == 0)
    {
        return {};
    }
    else {
        std::vector<Card *>returned = {};
        for (unsigned i = 0; i < num; i++)
        {
            returned.push_back(cards[i]);
            this->m_hand.addToHand(*cards[i]);
        }
        return this->m_hand.getHand();
    }
}


// BATTLE PHASE

int Player::checkOpponentGround(Player &opponent) {
       std::vector<Zone*>cards = opponent.field.monsterZone.m_monsterZone; //first monsterZone is field in player.h

       int i = 0;//second one is filed in monsterZone.h
       for (auto card : cards)
       {
           if (card->isEmpty() == false)
               i++;
       }
       return i;
}


// --------------------------------------------
// Operator overloads:
bool Player::operator==(const Player &other) const {
    return this->getPlayerName() == other.getPlayerName();
}

std::ostream &operator<<(std::ostream &out, Player &p){
    return out << "Player name: " << p.getPlayerName() << ", points " << p.getPlayerLifePoints()<<std::endl;
}




