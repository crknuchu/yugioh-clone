#include "headers/ui_mainwindow.h"
#include "headers/Game.h"
#include "headers/Monstercard.h"
#include "headers/EffectActivator.h"
#include "headers/MonsterZone.h"
#include "headers/SpellTrapZone.h"
#include "headers/Serializer.h"
#include "headers/Field.h"
#include "headers/Hand.h"

#include <iostream>
#include <random>
#include <map>
#include <functional>

#include <QGraphicsScene>
#include <QGraphicsLayout>

// Extern vars initialization:
Player *GameExternVars::pCurrentPlayer = nullptr;
Player *GameExternVars::pOtherPlayer = nullptr;
Card *GameExternVars::pCardToBePlacedOnField = nullptr;
Card *GameExternVars::pAttackingMonster = nullptr;

void delay()
{
    QTime dieTime= QTime::currentTime().addSecs(1);
    while (QTime::currentTime() < dieTime)
        QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
}

// QMainWindow != Ui::MainWindow

// Class definitions:
Game::Game(Player p1, Player p2,int lifePoints,int numberOfCards ,int timePerMove,QWidget *parent )
    : QMainWindow(parent),
      lifePoints(lifePoints),
      numberOfCards(numberOfCards),
      timePerMove(timePerMove),
      ui(new Ui::MainWindow),
      m_player1(p1),
      m_player2(p2)

{
    ui->setupUi(this);

    // Setup connections:
    setupConnections();

    /* Install an event filter for Resize event
       With this, we will be notified of every resize event on MainWindow
       We can use this to get new resolution after showFullscreen, whereas
       standard way of this->size() would return window size from the form designer,
       and not after going fullscreen.
       However, this only applies to this constructor (in other parts, this->size() can be used).
    */
    this->installEventFilter(this);

    // Create a new scene:
    scene = new QGraphicsScene(this);
    ui->graphicsView->setScene(scene);

}

Game::Game() {}

Game::~Game() {
    delete ui;
    delete scene;
}

int Game::getTimePerMove() const
{
    return timePerMove;
}

void Game::setTimePerMove(int newTimePerMove)
{
    timePerMove = newTimePerMove;
}

int Game::getNumberOfCards() const
{
    return numberOfCards;
}

void Game::setNumberOfCards(int newNumberOfCards)
{
    numberOfCards = newNumberOfCards;
}

int Game::getLifePoints() const
{
    return lifePoints;
}

void Game::setLifePoints(int newLifePoints)
{
    lifePoints = newLifePoints;
}

int Game::randomGenerator(const int limit) const {
  /*
   * Uniformly-distributed integer random number
   * generator that produces non-deterministic
   * random numbers.
   */
  std::random_device rd;

  /*
   *  A Mersenne Twister pseudo-random generator
   *  of 32-bit numbers with a state size of
   *  19937 bits.
   */
  std::mt19937 gen(rd());

  // Uniform distribution (from 1 to limit)
  std::uniform_int_distribution<> dis(1, limit);
  return dis(gen);
}

int Game::decideWhoPlaysFirst() const { return randomGenerator(2); }

void Game::switchPlayers() {
    Player *tmp = GameExternVars::pCurrentPlayer;
    GameExternVars::pCurrentPlayer = GameExternVars::pOtherPlayer;
    GameExternVars::pOtherPlayer = tmp;

    std::cout << "Current player is: " << *GameExternVars::pCurrentPlayer << std::endl;
    ui->labelCurrentPlayerDynamic->setText(QString::fromStdString(GameExternVars::pCurrentPlayer->getPlayerName()));
}

void Game::damageCalculation(Card *attackingMonster, Card *attackedMonster)
{
    MonsterCard* attacker = static_cast<MonsterCard*>(attackingMonster);
    MonsterCard* defender = static_cast<MonsterCard*>(attackedMonster);

    if(defender->getPosition() == Position::ATTACK)
    {
        std::cout << "Battle between 2 attacking monsters begins!" << std::endl;
        battleBetweenTwoAttackPositionMonsters(*attacker, *defender);
    }
    else
    {
        std::cout << "Battle against a defense position monster begins!" << std::endl;
        battleBetweenTwoDifferentPositionMonsters(*attacker, *defender);
    }
}

void Game::battleBetweenTwoAttackPositionMonsters(MonsterCard &attacker, MonsterCard &defender)
{
    int attackPointsDifference = attacker.getAttackPoints() - defender.getAttackPoints();
    if(attackPointsDifference < 0)
    {
        /* This means that the attacker is weaker than the defender
           In that case, attacker gets destroyed and the player
           that was controlling it takes damage. */

        /* TODO: This should be something like GameExternVars::pOtherPlayer->sendToGraveyard
                 Meanwhile, that Player's sendToGraveyard will actually call removeFromHand + sendToGraveyard */
        GameExternVars::pCurrentPlayer->field.graveyard->sendToGraveyard(attacker);
        damagePlayer(*GameExternVars::pCurrentPlayer, attackPointsDifference);
        std::cout << "The defender wins!" << std::endl;
    }
    else if(attackPointsDifference > 0)
    {
        /* TODO: This should be something like GameExternVars::pOtherPlayer->sendToGraveyard
                 Meanwhile, that Player's sendToGraveyard will actually call removeFromHand + sendToGraveyard */
        GameExternVars::pOtherPlayer->field.graveyard->sendToGraveyard(defender);
        damagePlayer(*GameExternVars::pOtherPlayer, attackPointsDifference);
        std::cout << "The attacker wins!" << std::endl;
    }
    else
    {
        /* This means that both attacking monsters had the same ATK.
         * In that case, both of them get destroyed, but no player takes damage. */
       GameExternVars::pCurrentPlayer->field.graveyard->sendToGraveyard(attacker);
       GameExternVars::pOtherPlayer->field.graveyard->sendToGraveyard(defender);

       std::cout << "Both monsters die!" << std::endl;
    }
}

void Game::battleBetweenTwoDifferentPositionMonsters(MonsterCard &attacker, MonsterCard &defender)
{
    int pointsDifference = attacker.getAttackPoints() - defender.getDefensePoints();
    if(pointsDifference < 0)
    {
        /* This means that the attacker is weaker than the defender.
         * Because the defender is in the DEFENSE position, attacker doesn't
         * get destroyed but the player controlling the attacker still takes damage. */
        damagePlayer(*GameExternVars::pCurrentPlayer, pointsDifference);
        std::cout << "The defender wins!" << std::endl;
    }
    else if(pointsDifference > 0)
    {
        /* If the attacker was stronger, the defender gets destroyed but the player
         * that was controlling the defender doesn't take damage because it was in
         * DEFENSE position. */

        /* TODO: This should be something like GameExternVars::pOtherPlayer->sendToGraveyard(defender)
                 Meanwhile, that Player's sendToGraveyard will actually call removeFromHand + sendToGraveyard */
        GameExternVars::pOtherPlayer->field.graveyard->sendToGraveyard(defender);
        std::cout << "The attacker wins!" << std::endl;
    }
    else
    {
        // If the pointsDifference is 0 then nothing happens
        std::cout << "No monster dies!" << std::endl;
    }

}

void Game::damagePlayer(Player &targetPlayer, int howMuch)
{
    // This assumes that howMuch is negative
    int newLifePoints = GameExternVars::pCurrentPlayer->getPlayerLifePoints() + howMuch;
    newLifePoints > 0 ? targetPlayer.setPlayerLifePoints(newLifePoints) : emit gameEndedAfterBattle(targetPlayer);
}

void Game::firstTurnSetup(float windowWidth, float windowHeight) {
  // The game decides who will play first:
  if (decideWhoPlaysFirst() == 1)
  {
      GameExternVars::pCurrentPlayer = &m_player1;
      GameExternVars::pOtherPlayer = &m_player2;
  }
  else
  {
      GameExternVars::pCurrentPlayer = &m_player2;
      GameExternVars::pOtherPlayer = &m_player1;
  }

  std::cout << "The first one to play is " << GameExternVars::pCurrentPlayer->getPlayerName() << std::endl;

  m_currentTurn = 1;
  GamePhaseExternVars::currentGamePhase = GamePhases::DRAW_PHASE;
  emit gamePhaseChanged(GamePhaseExternVars::currentGamePhase);

  // The first one gets 6 cards:
  GameExternVars::pCurrentPlayer->drawCards(6);

  // The other one gets 5 cards
  GameExternVars::pOtherPlayer->drawCards(5);



  GamePhaseExternVars::currentGamePhase = GamePhases::STANDBY_PHASE;
  emit gamePhaseChanged(GamePhaseExternVars::currentGamePhase);





  GamePhaseExternVars::currentGamePhase = GamePhases::MAIN_PHASE1;
  emit gamePhaseChanged(GamePhaseExternVars::currentGamePhase);





  //just a placeholder code for hand
  MonsterCard* testCard1 = new MonsterCard("Lord of D", 3000, 2500, 4,
                                              MonsterType::SPELLCASTER, MonsterKind::EFFECT_MONSTER,
                                              MonsterAttribute::DARK, false, Position::ATTACK, false,
                                              CardType::MONSTER_CARD, CardLocation::HAND,
                                              "Neither player can target Dragon monsters on the field with card effects.",
                                              ":/resources/pictures/blue_eyes.jpg"
                                              );
  SpellCard* testCard2 = new SpellCard(SpellType::NORMAL_SPELL, "Dian Keto the Cure Master",
                                             CardType::SPELL_CARD, CardLocation::HAND,
                                             "  Increase your Life Points by 1000 points.  ", ":/resources/pictures/DianKetotheCureMaster.jpg", true);

  MonsterCard* testCard3 = new MonsterCard("Lord of D", 3000, 2500, 4,
                                              MonsterType::SPELLCASTER, MonsterKind::EFFECT_MONSTER,
                                              MonsterAttribute::DARK, false, Position::ATTACK, false,
                                              CardType::MONSTER_CARD, CardLocation::HAND,
                                              "Neither player can target Dragon monsters on the field with card effects.",
                                              ":/resources/pictures/blue_eyes.jpg"
                                              );
//  ui->graphicsView->scene()->addWidget(testCard1->cardMenu);
//  testCard1->cardMenu->setVisible(false);e
//  ui->graphicsView->scene()->addWidget(testCard2->cardMenu);
//  testCard2->cardMenu->setVisible(false);
//  ui->graphicsView->scene()->addWidget(testCard3->cardMenu);
//  testCard3->cardMenu->setVisible(false);
//  ui->graphicsView->scene()->addItem(testCard1);
  emit GameExternVars::pCurrentPlayer->cardAddedToScene(*testCard1);
//  ui->graphicsView->scene()->addItem(testCard2);
  emit GameExternVars::pCurrentPlayer->cardAddedToScene(*testCard2);
//  ui->graphicsView->scene()->addItem(testCard3);
  emit GameExternVars::pCurrentPlayer->cardAddedToScene(*testCard3);
  GameExternVars::pCurrentPlayer->m_hand.setHandCoordinates(windowWidth, windowHeight);
  GameExternVars::pOtherPlayer->field.monsterZone.placeInMonsterZone(testCard3, 2); //testing purposes
  GameExternVars::pCurrentPlayer->m_hand.addToHand(*testCard1);
  GameExternVars::pCurrentPlayer->m_hand.addToHand(*testCard2);
}


// QT related stuff:
void Game::setupConnections() {
    // Game
    connect(this, &Game::mainWindowResized, this, &Game::onMainWindowResize);
    connect(this, &Game::gamePhaseChanged, this, &Game::onGamePhaseChange);
    connect(this, &Game::turnEnded, this, &Game::onTurnEnd);
    connect(&m_player1, &Player::cardAddedToScene, this, &Game::onCardAddedToScene);
    connect(&m_player2, &Player::cardAddedToScene, this, &Game::onCardAddedToScene);
    connect(this, &Game::gameEndedAfterBattle, this, &Game::onGameEnd); // Same slot for both game endings (one in EffectActivator and one here)

    // Buttons
    connect(ui->btnBattlePhase, &QPushButton::clicked, this, &Game::onBattlePhaseButtonClick);
    connect(ui->btnMainPhase2, &QPushButton::clicked, this, &Game::onMainPhase2ButtonClick);
    connect(ui->btnEndPhase, &QPushButton::clicked, this, &Game::onEndPhaseButtonClick);
}

bool Game::eventFilter(QObject *obj, QEvent *event)
{
    if(event->type() == QEvent::Resize)
    {
        QResizeEvent *resizeEvent = static_cast<QResizeEvent *>(event);

        // We need to emit the signal here so that we can scale the UI AFTER we catch it
        if (resizeEvent != nullptr)
            emit mainWindowResized(resizeEvent);

        return true;
    }
    else {
        return QObject::eventFilter(obj, event);
    }
}


// Slots:
void Game::onBattlePhaseButtonClick()
{
    std::cout << "Battle phase button clicked" << std::endl;
    GamePhaseExternVars::currentGamePhase = GamePhases::BATTLE_PHASE;
    emit gamePhaseChanged(GamePhaseExternVars::currentGamePhase);

    // Disable BP button so it can't be clicked again
    ui->btnBattlePhase->setEnabled(false);

    /* We enable Main Phase 2 button only if the BP button was clicked
     * since there can't be MP2 if there was no BP previously */
    ui->btnMainPhase2->setEnabled(true);
}

void Game::onMainPhase2ButtonClick()
{
    std::cout << "Main phase 2 button clicked" << std::endl;
    GamePhaseExternVars::currentGamePhase = GamePhases::MAIN_PHASE2;    
    emit gamePhaseChanged(GamePhaseExternVars::currentGamePhase);

    // Disable MP2 button so it can't be clicked again
    ui->btnMainPhase2->setEnabled(false);

    // Disable BP button
    ui->btnBattlePhase->setEnabled(false);
}

void Game::onEndPhaseButtonClick()
{
    std::cout << "End phase button clicked" << std::endl;
    GamePhaseExternVars::currentGamePhase = GamePhases::END_PHASE;

    // Set the label text to indicate that we are in the End Phase:
    emit gamePhaseChanged(GamePhaseExternVars::currentGamePhase);

    //... (something may happen here eventually)

    // TODO: More work is needed here...
    std::cout << "Turn " << m_currentTurn << " ends." << std::endl << std::endl;
    m_currentTurn++;
    emit turnEnded();

}

void Game::onGamePhaseChange(const GamePhases &newGamePhase)
{
    std::cout << "We are in onGamePhaseChange" << std::endl;

    // When game phase changes, we update label's text.
    // We use at() instead of [] because [] is not const and our map is.
    ui->labelGamePhase->setText(GamePhaseExternVars::gamePhaseToQString.at(newGamePhase));
}


/* This is actually a slot that does things at the beginning of a new turn
   so it could be called beginNewTurn or onNewTurn or something like that...*/
void Game::onTurnEnd() {
    // Reset the buttons
    ui->btnBattlePhase->setEnabled(true);
    ui->btnMainPhase2->setEnabled(false);



    // Switch the players:
    switchPlayers();
    std::cout << "After switchPlayers()" << std::endl;

    // The draw phase begins (this is not optional).
    GamePhaseExternVars::currentGamePhase = GamePhases::DRAW_PHASE;
    emit gamePhaseChanged(GamePhaseExternVars::currentGamePhase);

    // The current player draws a card (this is not optional).
    GameExternVars::pCurrentPlayer->drawCards(1);



    // The draw phase ends and the standby phase begins (this is not optional).
    GamePhaseExternVars::currentGamePhase = GamePhases::STANDBY_PHASE;
    emit gamePhaseChanged(GamePhaseExternVars::currentGamePhase);

    /* ... Something may happen here due to effects (maybe we should call checkEffects()
     or something similar that will check if there are effects to be activated in SP */



    // The standby phase ends and the main phase 1 begins (this is not optional).
    GamePhaseExternVars::currentGamePhase = GamePhases::MAIN_PHASE1;
    emit gamePhaseChanged(GamePhaseExternVars::currentGamePhase);

    // checkEffects(MAINPHASE1)
    // Main Phase 1 runs until user clicks one of the buttons.



    /* FIXME: Currently when EndPhase is clicked, labelGamePhase is instantly Main Phase 1
             because its switched so fast that we can't see DP and SP. */

}

/* In order to have drag resizes on the main window, we can place CentralWidget in a layout,
   but weird things tend to happen when we actually resize then, so for now its not done like that.*/
void Game::onMainWindowResize(QResizeEvent *resizeEvent)
{
//    std::cout << "Window has been resized!" << std::endl;
    this->counter++;
    if(counter == 2) {
        // Set our private variables to the new window size:
        m_windowWidth = resizeEvent->size().width();
        m_windowHeight = resizeEvent->size().height();

        // Check: Very rarely, this displays the same width/height as the old window
    //    std::cout << "New main window width/height: " << m_windowWidth << " / " << m_windowHeight << std::endl;

        // WIP: UI components
        // Game phase buttons and label:
        ui->labelGamePhase->setAlignment(Qt::AlignCenter);

        // Card info:
        ui->labelImage->setAlignment(Qt::AlignCenter);

        // TODO: getEffect()
    //    ui->textBrowserEffect->setText(testCard1->getEffect());

        QPixmap pix;
        pix.load(":/resources/blue_eyes.jpg");
        pix = pix.scaled(ui->labelImage->size(), Qt::KeepAspectRatio);
        ui->labelImage->setPixmap(pix);


        // GraphicsView and GraphicsScene adjustments:
        this->setWindowTitle("Yu-Gi-Oh!");
        ui->graphicsView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        ui->graphicsView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

        // We need to calculate other UI sizes so we know what QGraphicsView's size needs to be.
        // TODO: Change leftVerticalLayout name to something normal
        const int leftVerticalLayoutWidth = ui->leftVerticalLayout->sizeHint().width();
    //    qDebug("Layout Width: %d, height: %d", leftVerticalLayoutWidth, leftVerticalLayoutHeight);

        const int viewAndSceneWidth = m_windowWidth - (leftVerticalLayoutWidth);
        ui->graphicsView->setFixedSize(viewAndSceneWidth, m_windowHeight);
        ui->graphicsView->scene()->setSceneRect(0, 0, viewAndSceneWidth, m_windowHeight);

        // TODO: Check if this is needed
        ui->graphicsView->fitInView(0, 0, viewAndSceneWidth, m_windowHeight, Qt::KeepAspectRatio);

    //    std::cout << "Scene width: " << ui->graphicsView->scene()->width();

        // WIP: Background image
        // TODO: Find another image of the field
        QPixmap background(":/resources/pictures/space.jpeg");
        background = background.scaled(viewAndSceneWidth,  this->size().height() / 2, Qt::IgnoreAspectRatio);
        QBrush brush(QPalette::Window, background);
        ui->graphicsView->setBackgroundBrush(brush);

        m_player1.field.setField(1, viewAndSceneWidth,m_windowHeight);
        for(auto zone :    m_player1.field.monsterZone.m_monsterZone) {
            connect(zone, &Zone::zoneRedAndClicked, this, &Game::onRedZoneClick);
            connect(zone, &Zone::zoneGreenAndClicked, this, &Game::onGreenZoneClick);
            ui->graphicsView->scene()->addItem(zone);
        }
        for(auto zone : m_player1.field.spellTrapZone.m_spellTrapZone) {
            connect(zone, &Zone::zoneRedAndClicked, this, &Game::onRedZoneClick);
            connect(zone, &Zone::zoneGreenAndClicked, this, &Game::onGreenZoneClick);
            ui->graphicsView->scene()->addItem(zone);
        }
        for(auto c : m_player1.field.deck.uiDeck) {
            ui->graphicsView->scene()->addItem(c);
        }
        ui->graphicsView->scene()->addItem(m_player1.field.graveyard);
        ui->graphicsView->scene()->addItem(m_player1.field.fieldZone);

        m_player2.field.setField(2, viewAndSceneWidth,m_windowHeight);
        for(auto zone :    m_player2.field.monsterZone.m_monsterZone) {
            connect(zone, &Zone::zoneRedAndClicked, this, &Game::onRedZoneClick);
            connect(zone, &Zone::zoneGreenAndClicked, this, &Game::onGreenZoneClick);
            ui->graphicsView->scene()->addItem(zone);
        }
        for(auto zone : m_player2.field.spellTrapZone.m_spellTrapZone) {
            connect(zone, &Zone::zoneRedAndClicked, this, &Game::onRedZoneClick);
            connect(zone, &Zone::zoneGreenAndClicked, this, &Game::onGreenZoneClick);
            ui->graphicsView->scene()->addItem(zone);
        }
        for(auto c : m_player2.field.deck.uiDeck) {
            ui->graphicsView->scene()->addItem(c);
        }
        ui->graphicsView->scene()->addItem(m_player2.field.graveyard);
        ui->graphicsView->scene()->addItem(m_player2.field.fieldZone);

        // First turn setup at the beginning of the game:
        firstTurnSetup(viewAndSceneWidth, m_windowHeight);
    }
}

void Game::onCardHoverEnter(Card &card)
{
    std::cout << "Card " << card.getCardName() << " hover-entered!" << std::endl;
    ui->labelImage->setVisible(true);
    ui->textBrowserEffect->setVisible(true);
}
void Game::onCardHoverLeave(Card &card)
{
    std::cout << "Card " << card.getCardName() << " hover-left!" << std::endl;
    ui->labelImage->setVisible(false);
    ui->textBrowserEffect->setVisible(false);
}

void Game::onCardSelect(Card *card)
{
    std::cout << "Card name: " << card->getCardName() << std::endl;

    // Pseudo-code
    /* -> Call setCardMenu() that determines the appearance of card menu based on flags
     *  -> calls cardMenu.set() that sets the appropriate fields to false
    */
    card->setCardMenu();

    // Now we need to connect the card's menu UI to our slots
    /* We use a lambda here because QT's clicked() signal only sends a bool value of true/false
       This way, we can pass the card to our onActivateButtonClick slot */
    connect(card->cardMenu->activateButton, &QPushButton::clicked, this, [this, card](){
        onActivateButtonClick(*card);
    });

    connect(card->cardMenu->setButton, &QPushButton::clicked, this, [this, card](){
        onSetButtonClick(*card);
    });

    connect(card->cardMenu->summonButton, &QPushButton::clicked, this, [this, card](){
        onSummonButtonClick(*card);
    });

    connect(card->cardMenu->attackButton, &QPushButton::clicked, this, [this, card](){
        onAttackButtonClick(*card);
    });

    connect(this, &Game::activateFromHand, this, &Game::onActivateFromHand);

    // FIXME: After menu is closed once, 2 clicks are needed to get it to be shown again
    card->cardMenu->isVisible() == false ? card->cardMenu->show() : card->cardMenu->hide();
}

void Game::onActivateFromHand(Card &activatedCard) {
    //its only spell card for now that can be activated from hand
    GameExternVars::pCardToBePlacedOnField = &activatedCard;
    GameExternVars::pCurrentPlayer->field.spellTrapZone.colorFreeZones();
}

// Slots for card menu UI
void Game::onActivateButtonClick(Card &card)
{
    std::cout << "Activate button clicked on card " << card.getCardName() << std::endl;

    // Idea: Map of function pointers for effects
    const std::string cardName = card.getCardName();
    if(card.getCardLocation() == CardLocation::HAND) {
        emit activateFromHand(card);
    }
    else {
        // Effect activator is needed for effect handling
        EffectActivator effectActivator(card);

        // We connect every signal from EffectActivator to our slots in Game:
        connect(&effectActivator, &EffectActivator::healthPointsChanged, this, &Game::onHealthPointsChange);
        connect(&effectActivator, &EffectActivator::gameEnded, this, &Game::onGameEnd);

        // Activate the card's effect
        effectActivator.activateEffect(cardName);

        //if(shouldBeSentToGraveyard) this needs to be implemented
        delay();
        GameExternVars::pCurrentPlayer->sendToGraveyard(card);
    }
}

void Game::onSummonButtonClick(Card &card) {
    std::cout<< "Summon button was clicked on card " << card.getCardName() << std::endl;

    // Remove target card from player's hand
//    GameExternVars::pCurrentPlayer->m_hand.removeFromHand(card);
//    std::cout << "Hand after removing the card: " << std::endl;

    /* Set this card that is to-be-summoned to a global summon target, in order for Zone objects to be able
       to see it. */
    GameExternVars::pCardToBePlacedOnField = &card;
    std::cout << "Current summon target is: " << GameExternVars::pCardToBePlacedOnField->getCardName() << std::endl;

    // Color the free zones so user can select one to place.
    GameExternVars::pCurrentPlayer->field.monsterZone.colorFreeZones();

}

void Game::onAttackButtonClick(Card &attackingMonster)
{
   std::cout << "Attack button clicked" << std::endl;

   // Set the monster that initiated the attack as the global attacking monster
   GameExternVars::pAttackingMonster = &attackingMonster;

   // Color opponent's monsters
   // Placeholder for now, should be GameExternVars::pOtherPlayer->monsterZone.colorOccupiedZones() but that produces segfault
   GameExternVars::pOtherPlayer->field.monsterZone.colorOccupiedZones();
}


/* TODO: This should accept the targetPlayer as an argument, because otherwise we always print currentPlayer's hp,
         even if it was other player's health that had changed. */
void Game::onHealthPointsChange(Player &targetPlayer) // const?
{
    std::cout << "Current health points for player " << targetPlayer.getPlayerName() << " : "<< targetPlayer.getPlayerLifePoints() << std::endl;

    // Set the label text to the current turn player's health value
    ui->labelHealthPointsDynamic->setText(QString::fromStdString(std::to_string(GameExternVars::pCurrentPlayer->getPlayerLifePoints())));
}

void Game::onGameEnd(Player &loser)
{
    loser.setPlayerLifePoints(0);
    ui->labelHealthPointsDynamic->setText(QString::fromStdString("0"));
    std::cout << "The game has ended! Player " << loser.getPlayerName() << " has lost because his health points reached 0 !" << std::endl;

    // TODO: Stop the game here somehow!
}


void Game::onSetButtonClick(const Card &card)
{
    std::cout << "Set button clicked on card " << card.getCardName() << std::endl;
}

void Game::onRedZoneClick(Zone *clickedRedZone) {
    Card *card = GameExternVars::pCardToBePlacedOnField;

    std::cout << "Card " << *card << std::endl;


    // TODO: Move this into separate functions.
    if(card->getCardType() == CardType::MONSTER_CARD) {
        GameExternVars::pCurrentPlayer->field.monsterZone.placeInMonsterZone(card, clickedRedZone);
        card->setCardLocation(CardLocation::FIELD);
        GameExternVars::pCurrentPlayer->field.monsterZone.refresh();
    }
    else if(card->getCardType() == CardType::SPELL_CARD || card->getCardType() == CardType::TRAP_CARD) {
        GameExternVars::pCurrentPlayer->field.spellTrapZone.placeInSpellTrapZone(card, clickedRedZone);
        card->setCardLocation(CardLocation::FIELD);
        GameExternVars::pCurrentPlayer->field.spellTrapZone.refresh();
        card->cardMenu->activateButton->click(); //testing purposes
    }

    // FIXME: For some reason, when card is in the zone and we go fullscreen, right border of the zone goes under the card
//    card->move(clickedRedZone->m_x, clickedRedZone->m_y);
}

void Game::onGreenZoneClick(Zone *clickedGreenZone) {
    std::cout << "Green zone was clicked!" << std::endl;

    // TODO: MonsterCard instead of Card?
    Card* attackedMonster = clickedGreenZone->m_pCard;

    // Refresh the opponent's monster zone
    GameExternVars::pOtherPlayer->field.monsterZone.refresh();

    // Do the damage calculation
    damageCalculation(GameExternVars::pAttackingMonster, attackedMonster);


}

void Game::onCardAddedToScene(Card &card)
{
    connect(&card, &Card::cardSelected, this, &Game::onCardSelect);
    connect(&card, &Card::cardHoveredEnter, this, &Game::onCardHoverEnter);
    connect(&card, &Card::cardHoveredLeave, this, &Game::onCardHoverLeave);

    //Needed to show a card
    ui->graphicsView->scene()->addWidget(card.cardMenu);
    card.cardMenu->setVisible(false);
    if(card.scene()) {
        if(card.getCardType() == CardType::MONSTER_CARD) {
            MonsterCard* monsterCard = dynamic_cast<MonsterCard*>(&card);
            MonsterCard* cardCopy = new MonsterCard(*monsterCard);
            std::cout << "hej jel sam ovde" << std::endl;
            ui->graphicsView->scene()->addItem(cardCopy);
        }
    }
    else
     ui->graphicsView->scene()->addItem(&card);

    // By default we don't want to show card info unless the card is hovered
    ui->labelImage->setVisible(false);
    ui->textBrowserEffect->setVisible(false);
}
