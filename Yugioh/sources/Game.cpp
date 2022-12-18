#include "headers/ui_mainwindow.h"
#include "headers/Game.h"
#include "headers/Monstercard.h"
#include "headers/EffectActivator.h"
#include "headers/MonsterZone.h"
#include "headers/SpellTrapZone.h"

#include <iostream>
#include <random>
#include <map>
#include <functional>

#include <QGraphicsScene>
#include <QGraphicsLayout>
#include <QMessageBox>

// Extern vars initialization:
Player *GameExternVars::pCurrentPlayer = nullptr;
Player *GameExternVars::pOtherPlayer = nullptr;
Card *GameExternVars::pCardToBePlacedOnField = nullptr;
Card *GameExternVars::pAttackingMonster = nullptr;

// QMainWindow != Ui::MainWindow
MonsterZone monsterZone = MonsterZone();
SpellTrapZone spellTrapZone = SpellTrapZone();

// Class definitions:
Game::Game(Player p1, Player p2, QWidget *parent)
    : QMainWindow(parent),
      ui(new Ui::MainWindow),
      m_player1(p1),
      m_player2(p2),
      m_pTcpSocket(new QTcpSocket(this))

{
    ui->setupUi(this);

    // Setup data stream
    m_inDataStream.setDevice(m_pTcpSocket);
    m_inDataStream.setVersion(QDataStream::Qt_5_15);

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

    // First turn setup at the beginning of the game:
    firstTurnSetup();


    for(auto *zone : monsterZone.m_monsterZone) {
         connect(zone, &Zone::zoneRedAndClicked, this, &Game::onRedZoneClick);
         connect(zone, &Zone::zoneGreenAndClicked, this, &Game::onGreenZoneClick);
         ui->graphicsView->scene()->addItem(zone);
     }

    for(auto *zone : spellTrapZone.m_spellTrapZone) {
         connect(zone, &Zone::zoneRedAndClicked, this, &Game::onRedZoneClick);
         connect(zone, &Zone::zoneGreenAndClicked, this, &Game::onGreenZoneClick);
         ui->graphicsView->scene()->addItem(zone);
    }

    spellTrapZone.colorFreeZones();

    // Label setup:
    ui->labelCurrentPlayerDynamic->setText(QString::fromStdString(GameExternVars::pCurrentPlayer->getPlayerName()));

    /* TODO: This is only set here and never updated.
     * We should emit a signal in EffectActivator whenever the player loses/gains health and then catch it with a slot in game and call this line there.
     */

    ui->labelHealthPointsDynamic->setText(QString::fromStdString(std::to_string(GameExternVars::pCurrentPlayer->getPlayerLifePoints())));
}

Game::Game() {}

Game::~Game() {
    delete ui;
    delete scene;
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
        GameExternVars::pCurrentPlayer->graveyard.sendToGraveyard(attacker);
        damagePlayer(*GameExternVars::pCurrentPlayer, attackPointsDifference);
        std::cout << "The defender wins!" << std::endl;
    }
    else if(attackPointsDifference > 0)
    {
        /* TODO: This should be something like GameExternVars::pOtherPlayer->sendToGraveyard
                 Meanwhile, that Player's sendToGraveyard will actually call removeFromHand + sendToGraveyard */
        GameExternVars::pOtherPlayer->graveyard.sendToGraveyard(defender);
        damagePlayer(*GameExternVars::pOtherPlayer, attackPointsDifference);
        std::cout << "The attacker wins!" << std::endl;
    }
    else
    {
        /* This means that both attacking monsters had the same ATK.
         * In that case, both of them get destroyed, but no player takes damage. */
       GameExternVars::pCurrentPlayer->graveyard.sendToGraveyard(attacker);
       GameExternVars::pOtherPlayer->graveyard.sendToGraveyard(defender);

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
        GameExternVars::pOtherPlayer->graveyard.sendToGraveyard(defender);
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

void Game::firstTurnSetup() {
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

//  std::cout << "Current player's hand: ";
//  std::vector<Card*> currentPlayerHand = GameExternVars::pCurrentPlayer->hand.getHand();
//  for(Card* card : currentPlayerHand)
//      std::cout << card->getCardName() << ", ";
//  std::cout << std::endl;

  // The other one gets 5 cards
  GameExternVars::pOtherPlayer->drawCards(5);
}


// QT related stuff:
void Game::setupConnections() {
    // Game
    connect(this, &Game::mainWindowResized, this, &Game::onMainWindowResize);
    connect(this, &Game::gamePhaseChanged, this, &Game::onGamePhaseChange);
    connect(this, &Game::turnEnded, this, &Game::onTurnEnd);
    connect(this, &Game::cardAddedToScene, this, &Game::onCardAddedToScene);
    connect(this, &Game::gameEndedAfterBattle, this, &Game::onGameEnd); // Same slot for both game endings (one in EffectActivator and one here)

    // Buttons
    connect(ui->btnBattlePhase, &QPushButton::clicked, this, &Game::onBattlePhaseButtonClick);
    connect(ui->btnMainPhase2, &QPushButton::clicked, this, &Game::onMainPhase2ButtonClick);
    connect(ui->btnEndPhase, &QPushButton::clicked, this, &Game::onEndPhaseButtonClick);

    // Networking
    connect(m_pTcpSocket, &QIODevice::readyRead, this, &Game::onMessageIncoming);
    connect(m_pTcpSocket, &::QAbstractSocket::errorOccurred, this, &Game::onErrorOccurred);
    connect(ui->btnTestNetwork, &QPushButton::clicked, this, &Game::onTestNetworkButtonClick);
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

void Game::onCardAddedToScene(Card &card)
{
    connect(&card, &Card::cardSelected, this, &Game::onCardSelect);
    connect(&card, &Card::cardHoveredEnter, this, &Game::onCardHoverEnter);
    connect(&card, &Card::cardHoveredLeave, this, &Game::onCardHoverLeave);

    // By default we don't want to show card info unless the card is hovered
    ui->labelImage->setVisible(false);
    ui->textBrowserEffect->setVisible(false);
}

/* In order to have drag resizes on the main window, we can place CentralWidget in a layout,
   but weird things tend to happen when we actually resize then, so for now its not done like that.*/
void Game::onMainWindowResize(QResizeEvent *resizeEvent)
{
    /* TODO: Is there a way to make Qt only do one resize (immediately to the fullscreen resolution,
             instead of first resizing to the resolution that is same as in Designer (and only after that one
             doing a proper resize to fullscreen) */

    // Resize counter
    this->resizeCount++;
    std::cout << "Resize counter: " << resizeCount << std::endl;


    /* Initial setup (we need 2nd resize because that is the one when the window goes fullscreen)
       Here we initialize objects, etc. (so that they don't get initialized on every resize event) */
    if(resizeCount == 2)
    {
        std::cout << "We are in the fullscreen mode" << std::endl;


        // Set our private variables to the new window size:
        m_windowWidth = resizeEvent->size().width();
        m_windowHeight = resizeEvent->size().height();

        // Check: Very rarely, this displays the same width/height as the old window
    //    std::cout << "New main window width/height: " << m_windowWidth << " / " << m_windowHeight << std::endl;

        // FIXME: If this isn't dynamically allocated with "new", it doesn't get added to the scene
        MonsterCard *monsterCard1 = new MonsterCard("Lord of D", 3000, 2500, 4,
                                                    MonsterType::SPELLCASTER, MonsterKind::EFFECT_MONSTER,
                                                    MonsterAttribute::DARK, false, Position::ATTACK, false,
                                                    CardType::MONSTER_CARD, CardLocation::FIELD,
                                                    "Neither player can target Dragon monsters on the field with card effects."
                                                    );
        monsterCard1->setPos(450, 450);
        ui->graphicsView->scene()->addItem(monsterCard1);

        // Notify the game that a card was added.
        emit cardAddedToScene(*monsterCard1);

        // WIP: UI components
        // Game phase buttons and label:
        ui->labelGamePhase->setAlignment(Qt::AlignCenter);

        // Card info:
        ui->labelImage->setAlignment(Qt::AlignCenter);
        ui->textBrowserEffect->setText(QString::fromStdString(monsterCard1->getCardDescription()));

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
        const int viewAndSceneWidth = m_windowWidth - (leftVerticalLayoutWidth);
        ui->graphicsView->setFixedSize(viewAndSceneWidth, m_windowHeight);
        ui->graphicsView->scene()->setSceneRect(0, 0, viewAndSceneWidth, m_windowHeight);
        // TODO: Check if this is needed
        ui->graphicsView->fitInView(0, 0, viewAndSceneWidth, m_windowHeight, Qt::KeepAspectRatio);

        // Background image
        QPixmap background(":/resources/space.jpeg");
        background = background.scaled(viewAndSceneWidth,  this->size().height(), Qt::IgnoreAspectRatio);
        QBrush brush(QPalette::Window, background);
        ui->graphicsView->setBackgroundBrush(brush);









        // Testing green zones
        monsterZone.placeInMonsterZone(monsterCard1, monsterZone.m_monsterZone[1]);
    }
}


void Game::onCardSelect(Card *card)
{
    std::cout << "A card was added to the scene!" << std::endl;
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

    if(card->cardMenu->visible == false)
    {
        card->cardMenu->show();
        card->cardMenu->visible = true;
    }
    else
    {
        card->cardMenu->hide();
        card->cardMenu->visible = false;
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


// Slots for card menu UI
void Game::onActivateButtonClick(const Card &card)
{
    std::cout << "Activate button clicked on card " << card.getCardName() << std::endl;

    // Idea: Map of function pointers for effects
    const std::string cardName = card.getCardName();

    // Effect activator is needed for effect handling
    EffectActivator effectActivator;

    // We connect every signal from EffectActivator to our slots in Game:
    connect(&effectActivator, &EffectActivator::healthPointsChanged, this, &Game::onHealthPointsChange);
    connect(&effectActivator, &EffectActivator::gameEnded, this, &Game::onGameEnd);

    // Activate the card's effect
    effectActivator.activateEffect(cardName);

}

void Game::onSummonButtonClick(Card &card) {
    std::cout<< "Summon button was clicked on card " << card.getCardName() << std::endl;

    // Add target card from player's hand: (for testing purposes)
    GameExternVars::pCurrentPlayer->hand.addToHand(card);

    std::cout << "Hand before removing the card: " << std::endl;
    for(auto card : GameExternVars::pCurrentPlayer->hand.getHand())
        std::cout << card->getCardName() << std::endl;

    // Remove target card from player's hand
    GameExternVars::pCurrentPlayer->hand.removeFromHand(card);
    std::cout << "Hand after removing the card: " << std::endl;
    for(auto card : GameExternVars::pCurrentPlayer->hand.getHand())
        std::cout << card->getCardName() << std::endl;

    /* Set this card that is to-be-summoned to a global summon target, in order for Zone objects to be able
       to see it. */
    GameExternVars::pCardToBePlacedOnField = &card;
    std::cout << "Current summon target is: " << GameExternVars::pCardToBePlacedOnField->getCardName() << std::endl;

    // Color the free zones so user can select one to place.
    monsterZone.colorFreeZones();

}

void Game::onAttackButtonClick(Card &attackingMonster)
{
   std::cout << "Attack button clicked" << std::endl;

   // Set the monster that initiated the attack as the global attacking monster
   GameExternVars::pAttackingMonster = &attackingMonster;

   // Color opponent's monsters
   // Placeholder for now, should be GameExternVars::pOtherPlayer->monsterZone.colorOccupiedZones() but that produces segfault
   monsterZone.colorOccupiedZones();
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
    Card* card = GameExternVars::pCardToBePlacedOnField;

    // TODO: Move this into separate functions.
    if(card->getCardType() == CardType::MONSTER_CARD) {
        monsterZone.placeInMonsterZone(card, clickedRedZone);
        card->setCardLocation(CardLocation::FIELD);
        for(auto x : monsterZone.m_monsterZone) {
            if(!x->isEmpty())
                std::cout << *x->m_pCard << std::endl;
        }
        monsterZone.refresh();
    }
    else if(card->getCardType() == CardType::SPELL_CARD || card->getCardType() == CardType::TRAP_CARD) {
        spellTrapZone.placeInSpellTrapZone(card, clickedRedZone);
        card->setCardLocation(CardLocation::FIELD);
        for(auto x : spellTrapZone.m_spellTrapZone) {
            if(!x->isEmpty())
                std::cout << *x->m_pCard << std::endl;
        }
        spellTrapZone.refresh();
    }

    // FIXME: For some reason, when card is in the zone and we go fullscreen, right border of the zone goes under the card
    card->move(clickedRedZone->m_x, clickedRedZone->m_y);
}

void Game::onGreenZoneClick(Zone *clickedGreenZone) {
    std::cout << "Green zone was clicked!" << std::endl;

    // TODO: MonsterCard instead of Card?
    Card* attackedMonster = clickedGreenZone->m_pCard;

    // Refresh the opponent's monster zone
    monsterZone.refresh();

    // Do the damage calculation
    damageCalculation(GameExternVars::pAttackingMonster, attackedMonster);


}

void Game::onErrorOccurred(QAbstractSocket::SocketError socketError)
{
    switch (socketError) {
       case QAbstractSocket::RemoteHostClosedError:
           break;
       case QAbstractSocket::HostNotFoundError:
           QMessageBox::information(this, tr("Game client"),
                                    tr("The host was not found. Please check the "
                                       "host name and port settings."));
           break;
       case QAbstractSocket::ConnectionRefusedError:
           QMessageBox::information(this, tr("Game client"),
                                    tr("The connection was refused by the peer. "
                                       "Make sure the server is running, "
                                       "and check that the host name and port "
                                       "settings are correct."));
           break;
       default:
           QMessageBox::information(this, tr("Game client"),
                                    tr("The following error occurred: %1.")
                                    .arg(m_pTcpSocket->errorString()));
    }
}

void Game::onMessageIncoming()
{
    // Read data that was sent from the server
    m_inDataStream.startTransaction();

    QByteArray nextMessage;
    m_inDataStream >> nextMessage;

    std::cout << "Server Message: " << nextMessage.toStdString() << std::endl;

    if(!m_inDataStream.commitTransaction())
        return;
//    if(nextMessage == m_currentMessage)
//    {
//        QTimer::singleShot(0, this, &Client::onReadMessage);
//        return;
//    }

    m_messageFromServer = nextMessage;
    ui->labelMessageFromServer->setText(m_messageFromServer);
}

void Game::onTestNetworkButtonClick()
{
    ui->btnTestNetwork->setEnabled(false);

    m_pTcpSocket->abort();
    m_pTcpSocket->connectToHost("localhost" , 8090);
}
