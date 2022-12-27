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
            emit cardAddedToScene(*newCard);
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

    int cardInGrave = 0; //flag
    for (auto it = this->field.graveyard->cbegin(); it != this->field.graveyard->cend(); it++)
    {
        if ((*it) == &card) {
            cardInGrave = 1;
//            this->field.graveyard->removeFromGraveyard(*it);
            this->m_hand.addToHand(card);
            return;
        }
    }

    if (cardInGrave == 0)
    {
        std::cerr<<card.getCardName() << " card is not in grave, can't draw it back"<<std::endl;
        return;
    }


}

bool Player::isCardInGrave(Card &c)
{
    for (auto it = this->field.graveyard->cbegin(); it != this->field.graveyard->cend(); it++)
    {
        if ((*it) == &c)
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
        if (dynamic_cast<MonsterCard *>(&card) != nullptr)
        {
            this->field.monsterZone.colorFreeZones();
            this->field.monsterZone.placeInMonsterZone(&card, zoneNumber);
        }
        else if (dynamic_cast<SpellTrapZone *>(&card) != nullptr)
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
void Player::sendToGraveyard(Card &card, Zone* zone)
{
      zone->m_pCard = nullptr; //free space for that zone, card is sent to graveyard ===> zone.isEmpty() returns true after
      this->field.graveyard->sendToGraveyard(card);

}

void Player::sendToGraveyard(Card &card){
    //first need to be removed from field
    int position;
    try {
        //removing from deck, not sure if is it legal move
        for (auto it = this->field.deck.cbegin(); it != this->field.deck.cend(); it++){
            if ((*it) == &card){
//                this->field.deck.erase(it);
                this->field.graveyard->sendToGraveyard(card);
                std::cout<< (*it)->getCardName()<<" successfully removed from deck"<<std::endl;
                return;
            }
        }

        position = 0; //can't put this in for loop bcs of auto iterator
        for (auto it = this->field.monsterZone.m_monsterZone.cbegin(); it != this->field.monsterZone.m_monsterZone.cend(); it++, position++){
            if ((*it)->m_pCard == &card){
//                this->field.monsterZone.m_monsterZone.erase(it);//delete from vector of cards
                this->field.monsterZone.removeFromMonsterZone(position);
                this->field.graveyard->sendToGraveyard(card);
                std::cout<< (*it)->m_pCard->getCardName() <<" successfully removed from monsterZone"<<std::endl;
                return;
            }
        }
        position = 0;
        for (auto it = this->field.spellTrapZone.m_spellTrapZone.cbegin(); it != this->field.spellTrapZone.m_spellTrapZone.cend(); it++, position++){
            if ((*it)->m_pCard == &card){
//                this->field.spellTrapZone.m_spellTrapZone.erase(it);
                this->field.spellTrapZone.removeFromSpellTrapZone(position);
                this->field.graveyard->sendToGraveyard(card);
                return;
            }
        }

        for (auto it = this->m_hand.cbegin(); it != this->m_hand.cend(); it++){
            if ((*it) == &card){
//               this->m_hand.erase(it);
               this->field.graveyard->sendToGraveyard(card);
               std::cout<< (*it)->getCardName() << " succesfully removed from hand"<<std::endl;
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

// BATTLE PHASE

int Player::checkOpponentGround(Player &opponent) {
       std::vector<Zone*>cards = opponent.field.monsterZone.m_monsterZone; //first monsterZone is field in player.h
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

    GamePhases tmpPhase = GamePhaseExternVars::currentGamePhase;
    if (tmpPhase == GamePhases::BATTLE_PHASE){
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

std::ostream &operator<<(std::ostream &out, Player &p){
    return out << "Player name: " << p.getPlayerName() << ", points " << p.getPlayerLifePoints()<<std::endl;
}





//int Player::checkOpponentGround(Player &opponent) const {
//    // return opponent.m_tableMonsterCards.getMonsterZone().size();
//}
//void Player::attackOpponent(Game &game, MonsterCard m, Player &opponent){

//    // if (game.getGamePhase() == GamePhases::BATTLE_PHASE){
//    //     if (m.getCardType() == CardType::MONSTER_CARD){
//    //         if (0 == checkOpponentGround(opponent)){
//    //             opponent.setPlayerLifePoints(m.getAttackPoints());
//    //         }
//    //     }
//    //     else {
//    //         //TODO
//    //         //pick opponent card to fight()
//    //     }
//    // }
//    // else {
//    //     std::cerr<<"incompatibile game phase, can't attack at this moment"<<std::endl;
//    // }

//}

