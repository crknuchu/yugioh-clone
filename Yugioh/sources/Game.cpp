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
#include <QTimer>

// Extern vars initialization:
Player *GameExternVars::pCurrentPlayer = nullptr;
Player *GameExternVars::pOtherPlayer = nullptr;
Card *GameExternVars::pCardToBePlacedOnField = nullptr;
Card *GameExternVars::pAttackingMonster = nullptr;


// Placeholders
MonsterZone monsterZone = MonsterZone();
SpellTrapZone spellTrapZone = SpellTrapZone();


const std::map<QString, Game::DESERIALIZATION_MEMBER_FUNCTION_POINTER> Game::m_deserializationMap = {
    {"WELCOME_MESSAGE",             &Game::deserializeWelcomeMessage},
    {"START_GAME",                  &Game::deserializeStartGame},
    {"FIELD_PLACEMENT",             &Game::deserializeFieldPlacement},
    {"ADD_CARD_TO_HAND",            &Game::deserializeAddCardToHand},
    {"BATTLE",                      &Game::deserializeBattle}
};




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


    // TODO: We need to connect our players to the server in setupConnections.



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



// TODO: This can't happen in game, since we will have 2 clients/game instances which could potentially have different first player. !!
// We could have a extern var maybe that indicates who is first.
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
  // Notify the server that cards were drawn
  // FIXME: This is ugly
//  for(int i = 0; i < 6; i++)
//  {
//      QByteArray buffer;
//      QDataStream outDataStream(&buffer, QIODevice::WriteOnly);
//      outDataStream.setVersion(QDataStream::Qt_5_15);

//      outDataStream << QString::fromStdString("ADD_CARD_TO_HAND");
//      outDataStream << QString::fromStdString("OPPONENT"); // We tell the opposite player that his opponent (current player in this call) got 6 cards

//      sendDataToServer(buffer);
//  }



  // The other one gets 5 cards
  GameExternVars::pOtherPlayer->drawCards(5);
//  for(int i = 0; i < 5; i++)
//  {
//      QByteArray buffer;
//      QDataStream outDataStream(&buffer, QIODevice::WriteOnly);
//      outDataStream.setVersion(QDataStream::Qt_5_15);

//      outDataStream << QString::fromStdString("ADD_CARD_TO_HAND");
//      outDataStream << QString::fromStdString("MYSELF");

//      sendDataToServer(buffer);
//  }
}


// QT related stuff:
void Game::setupConnections() {
    // Game
    connect(this, &Game::mainWindowResized, this, &Game::onMainWindowResize);
    connect(this, &Game::gameStarted, this, &Game::onGameStart);
    connect(this, &Game::gamePhaseChanged, this, &Game::onGamePhaseChange);
    connect(this, &Game::turnEnded, this, &Game::onTurnEnd);
    connect(this, &Game::cardAddedToScene, this, &Game::onCardAddedToScene);
    connect(this, &Game::gameEndedAfterBattle, this, &Game::onGameEnd); // Same slot for both game endings (one in EffectActivator and one here)

    // Buttons
    connect(ui->btnBattlePhase, &QPushButton::clicked, this, &Game::onBattlePhaseButtonClick);
    connect(ui->btnMainPhase2, &QPushButton::clicked, this, &Game::onMainPhase2ButtonClick);
    connect(ui->btnEndPhase, &QPushButton::clicked, this, &Game::onEndPhaseButtonClick);

    // Networking
    connect(m_pTcpSocket, &QIODevice::readyRead, this, &Game::onDataIncoming);
    connect(m_pTcpSocket, &::QAbstractSocket::errorOccurred, this, &Game::onNetworkErrorOccurred);
    connect(ui->btnTestNetwork, &QPushButton::clicked, this, &Game::onTestNetworkButtonClick);
    connect(ui->btnWriteData, &QPushButton::clicked, this, &Game::onWriteDataButtonClick);



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

// Networking:
bool Game::sendDataToServer(QByteArray &data)
{
    if(m_pTcpSocket->state() == QAbstractSocket::ConnectedState)
    {
        // First we send the data's size
        m_pTcpSocket->write(QInt32ToQByteArray(data.size()));
        // Then we write the actual data
        m_pTcpSocket->write(data);
        return m_pTcpSocket->waitForBytesWritten();
    }
    else
    {
        std::cerr << "Error: the socket that is trying to write the data is in UNCONNECTED state!" << std::endl;
        return false;
    }
}

QByteArray Game::QInt32ToQByteArray(qint32 source)
{
    QByteArray tmp;
    QDataStream stream(&tmp, QIODevice::ReadWrite);
    stream << source;
    return tmp;
}

void Game::deserializeWelcomeMessage(QDataStream &deserializationStream)
{
    QString welcomeMessage;
    deserializationStream >> welcomeMessage;

    m_messageFromServer = welcomeMessage;
    ui->labelMessageFromServer->setText(m_messageFromServer);
}

void Game::deserializeStartGame(QDataStream &deserializationStream)
{
    std::cout << "We are in deserializeStartGame" << std::endl;
    // We don't actually have to deserialize something here, only emit a signal that will start the game
    emit gameStarted();

}

void Game::deserializeFieldPlacement(QDataStream &deserializationStream)
{
    /* If header was FIELD_PLACEMENT, we will get:
     * 1) Card's name
     * 2) Card's type
     * 3) Number of the zone that the card was placed in
     */


    QString cardName;
    QString cardType;
    qint32 zoneNumber;
    deserializationStream >> cardName
                          >> cardType
                          >> zoneNumber;


    std::cout << "Card info: " << std::endl;
    std::cout << "Card name: " << cardName.toStdString() << std::endl;
    std::cout << "Card type: " << cardType.toStdString() << std::endl;
    std::cout << "Zone number: " << zoneNumber << std::endl;


    // Placeholder
    /* Here, we will create the card by parsing JSON data that will be found based on card's name
       For now, we create a random card for testing purposes. */

    MonsterCard *testCard = new MonsterCard("Lord of D", 3000, 2500, 4,
                                                MonsterType::SPELLCASTER, MonsterKind::EFFECT_MONSTER,
                                                MonsterAttribute::DARK, false, Position::ATTACK, false,
                                                CardType::MONSTER_CARD, CardLocation::FIELD,
                                                "Neither player can target Dragon monsters on the field with card effects."
                                                );

    /* For now, position is hardcoded for testing purposes.
     * In the future, we will call a method that will put the card that was generated by json
     * in a zone (which will be determined by provided cardType and zoneNumber) */
    testCard->setPos(600, 600);
    ui->graphicsView->scene()->addItem(testCard);

    // Notify the game that a card was added.
    emit cardAddedToScene(*testCard);

}

void Game::deserializeAddCardToHand(QDataStream &deserializationStream)
{
    /* When player1 adds a card to the hand, game sends a header to the server to indicate that,
       and then we come here.
       In order for player2 (who is actually the CURRENT player while we are in this function)
       to changes in the opponent's (player1) hand, we just need to make other player draw one card.

       TODO: We need to somehow ensure that, for example player1's, decks are in sync, in both game sessions/clients.       !!

        // We don't want this player to see the opponent's hand, so we could potentially change the pixmap to card_back.jpg
    */

    // We need to check if the cards were given to us or the opponent
    QString whoGetsTheCards;
    deserializationStream >> whoGetsTheCards;

    // whoGetsTheCards will be MYSELF only if a player does something that gives a card to his opponent (or for example in firstTurnSetup where its mandatory).
    whoGetsTheCards == QString::fromStdString("MYSELF") ? GameExternVars::pCurrentPlayer->drawCards(1) : GameExternVars::pOtherPlayer->drawCards(1);
}

void Game::deserializeBattle(QDataStream &deserializationStream)
{

}

void Game::onGameStart()
{
    std::cout << "Game has started!" << std::endl;
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

    /* We only set that global nullptr when summon btn is clicked, however
     * we color spell/trap zone here before any button is clicked, so when those
     * zones are clicked, pCardToBePlacedOnField is still nullptr and so is card and
     * calling card->getCardType produces a segfault. */
//    spellTrapZone.colorFreeZones();

    // Label setup:
    ui->labelCurrentPlayerDynamic->setText(QString::fromStdString(GameExternVars::pCurrentPlayer->getPlayerName()));

    /* TODO: This is only set here and never updated.
     * We should emit a signal in EffectActivator whenever the player loses/gains health and then catch it with a slot in game and call this line there.
     */

    ui->labelHealthPointsDynamic->setText(QString::fromStdString(std::to_string(GameExternVars::pCurrentPlayer->getPlayerLifePoints())));
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

    // Notify the server
    QByteArray buffer;
    QDataStream outDataStream(&buffer, QIODevice::WriteOnly);
    outDataStream.setVersion(QDataStream::Qt_5_15);
    outDataStream << QString::fromStdString("ADD_CARD_TO_HAND");
    outDataStream << QString::fromStdString("OPPONENT"); // We tell the opposite player that his opponent (current player in this call) got a card
    sendDataToServer(buffer);



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
    if(card->getCardType() == CardType::MONSTER_CARD) { // We have a segfault because this card is nullptr
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


    // Testing serialization
    QByteArray buffer;
    QDataStream outDataStream(&buffer, QIODevice::WriteOnly);
    outDataStream.setVersion(QDataStream::Qt_5_15);


    // zoneNumber is a placeholder for the number of the zone in which the card was placed
    // Later,  we will have a method for getting this
    qint32 zoneNumber = 3;
    outDataStream << QString("FIELD_PLACEMENT") // header, so that server knows what data to expect after it
                  << QString::fromStdString(card->getCardName()) // We only send card's name, server will pass it to the other client and then that client will construct the card
                  << QString::fromStdString(card->getCardTypeString())
                  << zoneNumber;

    sendDataToServer(buffer);
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

void Game::onNetworkErrorOccurred(QAbstractSocket::SocketError socketError)
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

void Game::onDataIncoming()
{
    std::cout << "We are in onDataIncoming" << std::endl;
    // Read data that was sent from the server
    m_inDataStream.startTransaction();

    // Deserialization
    // First we need to check what header we have
    QString header;
    m_inDataStream >> header;

    std::cout << "Header: " << header.toStdString() << std::endl;
    // Then we call the appropriate deserialization method for that header:
    auto deserializationFunctionPointer = m_deserializationMap.at(header);
    (this->*deserializationFunctionPointer)(m_inDataStream);

    if(!m_inDataStream.commitTransaction())
        return;
//    if(nextMessage == m_messageFromServer)
//    {
//        QTimer::singleShot(0, this, &Game::onMessageIncoming);
//        return;
//    }
}

void Game::onTestNetworkButtonClick()
{
    ui->btnTestNetwork->setEnabled(false);

    // Parse the address and the port
    QString addr = ui->textEditAddress->toPlainText();
    int port = ui->textEditPort->toPlainText().toInt();
    // Connect to the server
    m_pTcpSocket->abort();
    m_pTcpSocket->connectToHost(addr , port);

}

void Game::onWriteDataButtonClick()
{
   // Testing

   GameExternVars::pCurrentPlayer->drawCards(5);
   QByteArray buffer;
   QDataStream outDataStream(&buffer, QIODevice::WriteOnly);
   outDataStream.setVersion(QDataStream::Qt_5_15);
   for(int i = 0; i < 5; i++)
   {


       outDataStream << QString::fromStdString("ADD_CARD_TO_HAND")
                     << QString::fromStdString("OPPONENT");
   }
   if(!sendDataToServer(buffer))
    {
       std::cerr << "Error in sendDataToServer function! " << std::endl;
       return;
   }
}
