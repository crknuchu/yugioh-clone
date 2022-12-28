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
qint32 GameExternVars::currentTurnClientID = -1;
std::vector<Card *> GameExternVars::yugiCards;
std::vector<Card *> GameExternVars::kaibaCards;

const std::map<QString, Game::DESERIALIZATION_MEMBER_FUNCTION_POINTER> Game::m_deserializationMap = {
    {"START_GAME",                                      &Game::deserializeStartGame},
    {"FIELD_PLACEMENT",                                 &Game::deserializeFieldPlacement},
    {"ADD_CARD_TO_HAND",                                &Game::deserializeAddCardToHand},
    {"BATTLE_BETWEEN_ATTACK_POSITION_MONSTERS",         &Game::deserializeBattleBetweenAttackPositionMonsters},
    {"BATTLE_BETWEEN_DIFFERENT_POSITION_MONSTERS",      &Game::deserializeBattleBetweenDifferentPositionMonsters},
    {"LP_CHANGE",                                       &Game::deserializeLpChange},
    {"DESERIALIZATION_FINISHED",                        &Game::deserializeDeserializationFinished},
    {"GAMEPHASE_CHANGED",                               &Game::deserializeGamePhaseChanged},
    {"NEW_TURN",                                        &Game::deserializeNewTurn},
    {"EFFECT_ACTIVATED",                                &Game::deserializeEffectActivated},
    {"REPOSITION",                                      &Game::deserializeReposition},
    {"DESTROY_CARD",                                    &Game::deserializeDestroyCard}
};

Game::Game(Player p1, Player p2,int lifePoints,int numberOfCards ,int timePerMove,QWidget *parent )
    : QMainWindow(parent),
      lifePoints(lifePoints),
      numberOfCards(numberOfCards),
      timePerMove(timePerMove),
      ui(new Ui::MainWindow),
      m_player1(p1),
      m_player2(p2),
      m_pTcpSocket(new QTcpSocket(this))

{
    ui->setupUi(this);

    // UI Configuration
    // Game phase buttons and label:
    ui->labelGamePhase->setAlignment(Qt::AlignCenter);

    // Card info:
    ui->labelImage->setAlignment(Qt::AlignCenter);

    // Disable textBrowser until hover
    ui->textBrowserEffect->setVisible(false);


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




    // Set the global decks of both players
        // TODO: Kaiba.json
    Serializer s;
    s.loadFromJson(":/resources/yugi.json");
    GameExternVars::yugiCards = s.getCards();
//    s.loadFromJson(":/resources/kaiba.json");

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

void Game::switchPlayers() {
    Player *tmp = GameExternVars::pCurrentPlayer;
    GameExternVars::pCurrentPlayer = GameExternVars::pOtherPlayer;
    GameExternVars::pOtherPlayer = tmp;

    std::cout << "Current player is: " << *GameExternVars::pCurrentPlayer << std::endl;
    ui->labelCurrentPlayerNameDynamic->setText(QString::fromStdString(GameExternVars::pCurrentPlayer->getPlayerName()));
    ui->labelOtherPlayerNameDynamic->setText(QString::fromStdString(GameExternVars::pOtherPlayer->getPlayerName()));

    // Switch clients too
    GameExternVars::currentTurnClientID == 1 ? GameExternVars::currentTurnClientID = 2 : GameExternVars::currentTurnClientID = 1;

    // Notify the server about the new turn beginning:
    QEventLoop blockingLoop;
    connect(this, &Game::deserializationFinished, &blockingLoop, &QEventLoop::quit);
    QByteArray buffer;
    QDataStream outDataStream(&buffer, QIODevice::WriteOnly);
    outDataStream.setVersion(QDataStream::Qt_5_15);
    outDataStream << QString::fromStdString("NEW_TURN")
                  << GameExternVars::currentTurnClientID; // We tell the opposite player that his opponent (current player in this call) got a card
    sendDataToServer(buffer);
    blockingLoop.exec();
}

void Game::damageCalculation(Card *attackingMonster, Card *attackedMonster)
{
    MonsterCard* attacker = static_cast<MonsterCard*>(attackingMonster);
    MonsterCard* defender = static_cast<MonsterCard*>(attackedMonster);

    if(defender->getPosition() == MonsterPosition::ATTACK)
    {
        std::cout << "Battle between 2 attacking monsters begins!" << std::endl;
        battleBetweenTwoAttackPositionMonsters(*attacker, *defender);
    }
    else
    {
        std::cout << "Battle between 2 different position monsters begins!" << std::endl;
        battleBetweenTwoDifferentPositionMonsters(*attacker, *defender);
    }

    // Set the alreadyAttack flag for attacker
    attacker->setAlreadyAttackedThisTurn(true);
}

void Game::battleBetweenTwoAttackPositionMonsters(MonsterCard &attacker, MonsterCard &defender)
{
    /* TODO: We can also send the name of player who initiated the attack to the server,
             but its always the current player so maybe its not needed. */

    int attackPointsDifference = attacker.getAttackPoints() - defender.getAttackPoints();
    if(attackPointsDifference < 0)
    {
        /* This means that the attacker is weaker than the defender
           In that case, attacker gets destroyed and the player
           that was controlling it takes damage. */

        std::cout << "The defender wins!" << std::endl;

        QEventLoop blockingLoop;
        connect(this, &Game::deserializationFinished, &blockingLoop, &QEventLoop::quit);

        // We need the destroyed monster's zone number
        qint32 attackerZoneNumber = findZoneNumber(attacker, GameExternVars::pCurrentPlayer);

        // Find the zone that holds the destroyed card
        Zone *pZoneOfTheDestroyedCard = findZone(attackerZoneNumber, QString::fromStdString("monster card"), GameExternVars::pCurrentPlayer);
        Card *pDestroyedCard = pZoneOfTheDestroyedCard->m_pCard;

        // Actually destroy it
        GameExternVars::pCurrentPlayer->sendToGraveyard(*pDestroyedCard, pZoneOfTheDestroyedCard);


        // TODO: We can move this into a separate function
        QByteArray buffer;
        QDataStream outDataStream(&buffer, QIODevice::WriteOnly);
        outDataStream.setVersion(QDataStream::Qt_5_15);
        outDataStream << QString::fromStdString("DESTROY_CARD") // Notify the server that a card was destroyed
                      << QString::fromStdString("CURRENT_PLAYER") // Who owns a card that was destroyed
                      << QString::fromStdString(attacker.getCardTypeString())
                      << attackerZoneNumber; // Where is the monster card located
        sendDataToServer(buffer);
        blockingLoop.exec();

        damagePlayer(*GameExternVars::pCurrentPlayer, attackPointsDifference);
    }
    else if(attackPointsDifference > 0)
    {
//        damagePlayer(*GameExternVars::pOtherPlayer, attackPointsDifference);
        std::cout << "The attacker wins!" << std::endl;

        /* We want to notify the server about the battle outcome.
         * We also have to use QEventLoop to make this client wait until client 2 sends DESERIALIZATION_FINISHED
         *  (which will get sent to this client by the server) by making it loop until its built-in slot quit() is
         *  triggered by our deserializationFinished signal.
         *
         *  IMPORTANT: In theory its possible that deserializationFinished is emitted before we enter loop.exec(),
         *  which would leave us in an infinite loop, but that will practically never happen since that signal
         *  is emitted after a lot of other operations (send to server -> relay to another client -> send back -> emit)
         *  so we will always enter the loop before that.
         *
         *  TODO: We can make sure that this won't happen by using singleshot QTimer instead of a standard emit call */

        QEventLoop blockingLoop; // TODO: We can probably reuse blockingLoop
        connect(this, &Game::deserializationFinished, &blockingLoop, &QEventLoop::quit);

        // We need the destroyed monster's zone number
        qint32 defenderZoneNumber = findZoneNumber(defender, GameExternVars::pOtherPlayer);

        // TODO: These 3 lines can be a separate function since they are reused a lot in these battle functions
        // We need to find zone of the destroyed card
        Zone *pZoneOfTheDestroyedCard = findZone(defenderZoneNumber, QString::fromStdString("monster card"), GameExternVars::pOtherPlayer);
        Card *pDestroyedCard = pZoneOfTheDestroyedCard->m_pCard;

        // Actually destroy it
        GameExternVars::pOtherPlayer->sendToGraveyard(*pDestroyedCard, pZoneOfTheDestroyedCard);

        QByteArray buffer;
        QDataStream outDataStream(&buffer, QIODevice::WriteOnly);
        outDataStream.setVersion(QDataStream::Qt_5_15);
        outDataStream << QString::fromStdString("DESTROY_CARD") // Notify the server that a card was destroyed
                      << QString::fromStdString("OTHER_PLAYER") // Who owns a card that was destroyed
                      << QString::fromStdString(defender.getCardTypeString())
                      << defenderZoneNumber; // Where is the monster card located
        sendDataToServer(buffer);
        blockingLoop.exec();

        damagePlayer(*GameExternVars::pOtherPlayer, attackPointsDifference);
    }
    else
    {
        /* This means that both attacking monsters had the same ATK.
         * In that case, both of them get destroyed, but no player takes damage. */
        std::cout << "Both monsters die!" << std::endl;

        // First we destroy the attacker
        QEventLoop blockingLoopAttacker;
        connect(this, &Game::deserializationFinished, &blockingLoopAttacker, &QEventLoop::quit);

        qint32 attackerZoneNumber = findZoneNumber(attacker, GameExternVars::pCurrentPlayer);
        Zone *pZoneOfTheDestroyedCard = findZone(attackerZoneNumber, QString::fromStdString("monster card"), GameExternVars::pCurrentPlayer);
        Card *pDestroyedCard = pZoneOfTheDestroyedCard->m_pCard;
        GameExternVars::pCurrentPlayer->sendToGraveyard(*pDestroyedCard, pZoneOfTheDestroyedCard);

        // Notify the server
        QByteArray buffer;
        QDataStream outDataStream(&buffer, QIODevice::WriteOnly);
        outDataStream.setVersion(QDataStream::Qt_5_15);
        outDataStream << QString::fromStdString("DESTROY_CARD") // Notify the server that a card was destroyed
                      << QString::fromStdString("CURRENT_PLAYER") // Who owns a card that was destroyed
                      << QString::fromStdString(attacker.getCardTypeString())
                      << attackerZoneNumber; // Where is the monster card located
        sendDataToServer(buffer);
        blockingLoopAttacker.exec();

        // Now destroy the defender
        QEventLoop blockingLoopDefender;
        connect(this, &Game::deserializationFinished, &blockingLoopDefender, &QEventLoop::quit);

        qint32 defenderZoneNumber = findZoneNumber(defender, GameExternVars::pOtherPlayer);

        pZoneOfTheDestroyedCard = findZone(defenderZoneNumber, QString::fromStdString("monster card"), GameExternVars::pOtherPlayer);
        pDestroyedCard = pZoneOfTheDestroyedCard->m_pCard;
        GameExternVars::pOtherPlayer->sendToGraveyard(*pDestroyedCard, pZoneOfTheDestroyedCard);

        // Notify the server
        QByteArray buffer2;
        QDataStream outDataStream2(&buffer2, QIODevice::WriteOnly);
        outDataStream2.setVersion(QDataStream::Qt_5_15);
        outDataStream2 << QString::fromStdString("DESTROY_CARD") // Notify the server that a card was destroyed
                       << QString::fromStdString("OTHER_PLAYER") // Who owns a card that was destroyed
                       << QString::fromStdString(defender.getCardTypeString())
                       << defenderZoneNumber; // Where is the monster card located
        sendDataToServer(buffer2);
        blockingLoopDefender.exec();
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
        std::cout << "The defender wins!" << std::endl;

        damagePlayer(*GameExternVars::pCurrentPlayer, pointsDifference);
    }
    else if(pointsDifference > 0)
    {
        /* If the attacker was stronger, the defender gets destroyed but the player
         * that was controlling the defender doesn't take damage because it was in
         * DEFENSE position. */
        std::cout << "The attacker wins!" << std::endl;
        QEventLoop blockingLoop;
        connect(this, &Game::deserializationFinished, &blockingLoop, &QEventLoop::quit);

        // We need the destroyed monster's zone number
        qint32 defenderZoneNumber = findZoneNumber(defender, GameExternVars::pOtherPlayer);
        Zone *pZoneOfTheDestroyedCard = findZone(defenderZoneNumber, QString::fromStdString("monster card"), GameExternVars::pOtherPlayer);
        Card *pDestroyedCard = pZoneOfTheDestroyedCard->m_pCard;
        GameExternVars::pOtherPlayer->sendToGraveyard(*pDestroyedCard, pZoneOfTheDestroyedCard);

        QByteArray buffer;
        QDataStream outDataStream(&buffer, QIODevice::WriteOnly);
        outDataStream.setVersion(QDataStream::Qt_5_15);
        outDataStream << QString::fromStdString("DESTROY_CARD") // Notify the server that a card was destroyed
                      << QString::fromStdString("OTHER_PLAYER") // Who owns a card that was destroyed
                      << QString::fromStdString(defender.getCardTypeString())
                      << defenderZoneNumber; // Where is the monster card located
        sendDataToServer(buffer);
        blockingLoop.exec();
    }
    else
    {
        // If the pointsDifference is 0 then nothing happens
        std::cout << "No monster dies!" << std::endl;
    }
}

void Game::damagePlayer(Player &targetPlayer, int howMuch)
{
    int newLifePoints;
    howMuch > 0 ?  newLifePoints = targetPlayer.getPlayerLifePoints() - howMuch
                :  newLifePoints = targetPlayer.getPlayerLifePoints() + howMuch;
    if(newLifePoints > 0)
    {
        targetPlayer.setPlayerLifePoints(newLifePoints);
        emit lifePointsChanged(targetPlayer);
    }
    else
        emit gameEndedAfterBattle(targetPlayer);
}

Card* Game::reconstructCard(QString cardName)
{
    for(Card *card : GameExternVars::yugiCards)
    {
        if(card->getCardName() == cardName.toStdString())
            return card;
    }

    return nullptr;
}

qint32 Game::findZoneNumber(Card &targetCard, Player *pWhoOwnsIt)
{
    qint32 zoneNumber = 1;
    std::vector<Zone *> targetPartOfField;

    targetCard.getCardType() == CardType::MONSTER_CARD
        ? targetPartOfField = pWhoOwnsIt->field.monsterZone.m_monsterZone
        : targetPartOfField = pWhoOwnsIt->field.spellTrapZone.m_spellTrapZone;

    for(Zone *zone : targetPartOfField)
    {
        Card *tmpCard = zone->m_pCard;
        if(tmpCard != nullptr)
        {
            if(targetCard.getCardName() == tmpCard->getCardName())
                break;
        }
        zoneNumber++;
    }

    return zoneNumber;
}

Zone *Game::findZone(qint32 zoneNumber, QString cardType, Player *pTargetPlayer)
{
    std::vector<Zone *> partOfField;
    cardType == "monster card"
            ? partOfField = pTargetPlayer->field.monsterZone.m_monsterZone
            : partOfField = pTargetPlayer->field.spellTrapZone.m_spellTrapZone;

    return partOfField[zoneNumber - 1];
}

void Game::visuallySetMonster(MonsterCard *pMonsterCard)
{
    QPixmap pix;
    pix.load(":/resources/pictures/card_back.jpg");
    pix = pix.scaled(QSize(pMonsterCard->width, pMonsterCard->height), Qt::KeepAspectRatio);
    QTransform transformationMatrix;
    transformationMatrix.rotate(90);
    pMonsterCard->setPixmap(pix.transformed(transformationMatrix));

    // TODO: Center the card
}

void Game::visuallySetSpell(SpellCard *pSpellCard)
{
    QPixmap pix;
    pix.load(":/resources/pictures/card_back.jpg");
    pix = pix.scaled(QSize(pSpellCard->width, pSpellCard->height), Qt::KeepAspectRatio);
    pSpellCard->setPixmap(pix);
}

void Game::visuallySetTrap(TrapCard *pTrapCard)
{
    QPixmap pix;
    pix.load(":/resources/pictures/card_back.jpg");
    pix = pix.scaled(QSize(pTrapCard->width, pTrapCard->height), Qt::KeepAspectRatio);
    pTrapCard->setPixmap(pix);
}




void Game::firstTurnSetup(qint32 firstToPlay, qint32 clientID, float windowWidth, float windowHeight)
{

    std::cout << "Window width/height in firstTurnSetup: " << windowWidth << " / " << windowHeight << std::endl;

  // Disable UI for second player until its his turn.
    // TODO: Move this into a separate function since its used in onTurnEnd too.
    if(m_clientID != firstToPlay)
    {
      this->ui->btnBattlePhase->setEnabled(false);
      this->ui->btnEndPhase->setEnabled(false);
    }

    std::cout << "The first one to play is " << GameExternVars::pCurrentPlayer->getPlayerName() << std::endl;
    m_currentTurn = 1;

    GamePhaseExternVars::currentGamePhase = GamePhases::DRAW_PHASE;
    ui->labelGamePhase->setText(QString::fromStdString("DRAW PHASE")); // We hardcode it here since both clients are in sync here

    // The first one gets 6 cards:
    GameExternVars::pCurrentPlayer->drawCards(6);
    // The other one gets 5 cards
    GameExternVars::pOtherPlayer->drawCards(5);

    GamePhaseExternVars::currentGamePhase = GamePhases::STANDBY_PHASE;
    ui->labelGamePhase->setText(QString::fromStdString("STANDBY PHASE"));

    GamePhaseExternVars::currentGamePhase = GamePhases::MAIN_PHASE1;
    ui->labelGamePhase->setText(QString::fromStdString("MAIN PHASE 1"));


   // Just a placeholder code for hand
    MonsterCard* monsterCard1 = new MonsterCard("Trap Master", 3000, 2500, 4,
                                              MonsterType::SPELLCASTER, MonsterKind::EFFECT_MONSTER,
                                              MonsterAttribute::DARK, false, MonsterPosition::ATTACK, false,
                                              CardType::MONSTER_CARD, CardLocation::HAND,
                                              "Neither player can target Dragon monsters on the field with card effects.",
                                              ":/resources/pictures/TrapMaster.jpg"
                                              );
    MonsterCard* monsterCard2 = new MonsterCard("Trap Master", 3000, 2500, 4,
                                              MonsterType::SPELLCASTER, MonsterKind::EFFECT_MONSTER,
                                              MonsterAttribute::DARK, false, MonsterPosition::ATTACK, false,
                                              CardType::MONSTER_CARD, CardLocation::HAND,
                                              "Neither player can target Dragon monsters on the field with card effects.",
                                              ":/resources/pictures/TrapMaster.jpg"
                                              );
    MonsterCard* monsterCard3 = new MonsterCard("Lord of D", 1200, 2500, 4,
                                              MonsterType::SPELLCASTER, MonsterKind::EFFECT_MONSTER,
                                              MonsterAttribute::DARK, false, MonsterPosition::ATTACK, false,
                                              CardType::MONSTER_CARD, CardLocation::FIELD,
                                              "Neither player can target Dragon monsters on the field with card effects.",
                                              ":/resources/pictures/LordofD.jpg"
                                              );
    SpellCard* spellCard1 = new SpellCard(SpellType::NORMAL_SPELL, "Dark Hole", CardType::SPELL_CARD, CardLocation::HAND,
                                            SpellTrapPosition::NONE, "Destroy all monsters on the field.", ":/resources/pictures/DarkHole.jpg", false);

    ui->graphicsView->scene()->addItem(monsterCard1);
    ui->graphicsView->scene()->addWidget(monsterCard1->cardMenu);
    monsterCard1->cardMenu->setVisible(false);
    emit cardAddedToScene(monsterCard1);

    ui->graphicsView->scene()->addItem(monsterCard2);
    ui->graphicsView->scene()->addWidget(monsterCard2->cardMenu);
    monsterCard2->cardMenu->setVisible(false);
    emit cardAddedToScene(monsterCard2);

    ui->graphicsView->scene()->addItem(monsterCard3);
    ui->graphicsView->scene()->addWidget(monsterCard3->cardMenu);
    monsterCard3->cardMenu->setVisible(false);
    emit cardAddedToScene(monsterCard3);

    ui->graphicsView->scene()->addItem(spellCard1);
    ui->graphicsView->scene()->addWidget(spellCard1->cardMenu);
    spellCard1->cardMenu->setVisible(false);
    emit cardAddedToScene(spellCard1);

    GameExternVars::pCurrentPlayer->m_hand.setHandCoordinates(windowWidth, windowHeight);
    GameExternVars::pCurrentPlayer->m_hand.addToHand(*monsterCard1);
    GameExternVars::pCurrentPlayer->m_hand.addToHand(*monsterCard2);
    GameExternVars::pCurrentPlayer->m_hand.addToHand(*spellCard1);

    // Testing
    QTransform transformationMatrix;
    transformationMatrix.rotate(180);
    monsterCard3->setPixmap(monsterCard3->pixmap().transformed(transformationMatrix));
    GameExternVars::pOtherPlayer->field.monsterZone.placeInMonsterZone(monsterCard3, 2); //testing purposes

      // TODO: Disable clicks on the cards if its possible, or at least disable card menu for every card that this player has.
        // For loops with pCurrentPlayer and pOtherPlayer's hand and disable each card's menu
            // Important: don't forget to reenable it in onTurnEnd or switchPlayers



    // Label setup:
    ui->labelCurrentPlayerNameDynamic->setText(QString::fromStdString(GameExternVars::pCurrentPlayer->getPlayerName()));
    ui->labelOtherPlayerNameDynamic->setText(QString::fromStdString(GameExternVars::pOtherPlayer->getPlayerName()));

    ui->labelCurrentPlayerLpDynamic->setText(QString::fromStdString(std::to_string(GameExternVars::pCurrentPlayer->getPlayerLifePoints())));
    ui->labelOtherPlayerLpDynamic->setText(QString::fromStdString(std::to_string(GameExternVars::pOtherPlayer->getPlayerLifePoints())));
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
    connect(this, &Game::lifePointsChanged, this, &Game::onLifePointsChange);
    connect(GameExternVars::pCurrentPlayer, &Player::cardDrawn, this, &Game::onCardDraw);
    connect(GameExternVars::pOtherPlayer, &Player::cardDrawn, this, &Game::onCardDraw);

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

void Game::notifyServerThatDeserializationHasFinished()
{
    QByteArray buffer;
    QDataStream outDataStream(&buffer, QIODevice::WriteOnly);
    outDataStream.setVersion(QDataStream::Qt_5_15);

    outDataStream << QString::fromStdString("DESERIALIZATION_FINISHED");
    sendDataToServer(buffer);
}

QByteArray Game::QInt32ToQByteArray(qint32 source)
{
    QByteArray tmp;
    QDataStream stream(&tmp, QIODevice::ReadWrite);
    stream << source;
    return tmp;
}

void Game::deserializeStartGame(QDataStream &deserializationStream)
{
    std::cout << "We are in deserializeStartGame" << std::endl;

    // We need to see who plays first
    qint32 firstToPlay, clientID;

    deserializationStream >> firstToPlay
                          >> clientID;
    std::cout << "deserializeStartGame clientID: " << clientID << std::endl;

    emit gameStarted(firstToPlay, clientID);
}

void Game::deserializeFieldPlacement(QDataStream &deserializationStream)
{
    // TODO: There are still things here to be done, like reconstructing the cards and summoning them in correct zone and position


    QString cardName;
    QString cardType;
    qint32 zoneNumber;
    QString positionQString;
    deserializationStream >> cardName
                          >> cardType
                          >> zoneNumber
                          >> positionQString;

    std::cout << "Card info: " << std::endl;
    std::cout << "Card name: " << cardName.toStdString() << std::endl;
    std::cout << "Card type: " << cardType.toStdString() << std::endl;
    std::cout << "Zone number: " << zoneNumber << std::endl;
    std::cout << "Card position: " << positionQString.toStdString() << std::endl;



    // TODO: Here we will recreate the card in the future and put it in the correct zone.
    Card* targetCard = reconstructCard(cardName);


    std::cout << *targetCard << std::endl;
    if(targetCard == nullptr)
    {
        std::cerr << "reconstructCard() failed in deserializeFieldPlacement!" << std::endl;
        return;
    }

    // Add the card to the scene
    ui->graphicsView->scene()->addItem(targetCard);

    if (cardType == "monster card")
    {
        MonsterCard *monsterCard = static_cast<MonsterCard *>(targetCard);

        // Set the position
        MonsterPosition monsterPosition = monsterCard->monsterPositionQStringToEnum.at(positionQString);
        monsterCard->setPosition(monsterPosition);

        // If monster is set we need to make it appear so
        if(monsterPosition == MonsterPosition::FACE_DOWN_DEFENSE)
            visuallySetMonster(monsterCard);

        // Place it on the field
        GameExternVars::pCurrentPlayer->field.monsterZone.placeInMonsterZone(targetCard, zoneNumber);
    }
    else
    {
        SpellTrapPosition stPosition;
        if(cardType == "spell card")
        {
            SpellCard *spellCard = static_cast<SpellCard *>(targetCard);
            stPosition = spellCard->spellTrapPositionQStringToEnum.at(positionQString);
            spellCard->setPosition(stPosition);

            // Visually set it
            visuallySetSpell(spellCard);
        }
        else
        {
            TrapCard *trapCard = static_cast<TrapCard *>(targetCard);
            stPosition = trapCard->spellTrapPositionQStringToEnum.at(positionQString);
            trapCard->setPosition(stPosition);
            visuallySetTrap(trapCard);
        }
        GameExternVars::pCurrentPlayer->field.spellTrapZone.placeInSpellTrapZone(targetCard, zoneNumber);
    }


    // Rotate it by 180 degrees to be facing towards us
    QTransform transformationMatrix;
    transformationMatrix.rotate(180);
    targetCard->setPixmap(targetCard->pixmap().transformed(transformationMatrix));


    // Notify the server that deserialization is finished.
    notifyServerThatDeserializationHasFinished();
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

    // First we check how many cards do we need to draw
    qint32 numOfCards;
    deserializationStream >> numOfCards;

    // Then we check which player draws them
    QString whoGetsTheCards;
    deserializationStream >> whoGetsTheCards;

    // Actually draw the cards
    whoGetsTheCards == QString::fromStdString("CURRENT_PLAYER") ? GameExternVars::pCurrentPlayer->drawCards(numOfCards) : GameExternVars::pOtherPlayer->drawCards(numOfCards);


    notifyServerThatDeserializationHasFinished();
}

void Game::deserializeBattleBetweenAttackPositionMonsters(QDataStream &deserializationStream)
{
    std::cout << "Battle between 2 attacking monsters begins!" << std::endl;
    // We first check who won ("ATTACKER", "DEFENDER", "NOONE")
    QString whoWon;
    deserializationStream >> whoWon;

    // If whoWon was NOONE, then both monsters got destroyed
    if(whoWon == QString::fromStdString("NOONE"))
    {
        QString playerWhoInitiatedAttack, attackerCardName, defenderCardName;
        qint32 attackerZoneNumber, defenderZoneNumber;

        deserializationStream >> playerWhoInitiatedAttack
                              >> attackerCardName
                              >> defenderCardName
                              >> attackerZoneNumber
                              >> defenderZoneNumber;

        std::cout << "Both monsters die!" << std::endl;

        // TODO: Reconstruct the Card objects from card names
            /* Is this even needed? They will already be reconstructed when we deserialize the summons,
             * so we could just do destroyMonster() probably, after we get the pointer to both monsters */

        // TODO: Call destroyMonster() that will be implemented, for both monsters.
    }
    else if(whoWon == QString::fromStdString("ATTACKER"))
    {
        QString defenderCardName;
        qint32 defenderZoneNumber;
        deserializationStream >> defenderCardName
                              >> defenderZoneNumber;

        std::cout << "The opponent's attacker monster wins!" << std::endl;
        // TODO: get a pointer to the defender
        // TODO: currentPlayer->destroyMonster(defender)
    }
    else
    {
        QString attackerCardName;
        qint32 attackerZoneNumber;

        deserializationStream >> attackerCardName
                              >> attackerZoneNumber;
        std::cout << "The defender wins!" << std::endl;
    }


    notifyServerThatDeserializationHasFinished();
}

void Game::deserializeBattleBetweenDifferentPositionMonsters(QDataStream &deserializationStream)
{
    std::cout << "Battle between 2 different position monsters begins!" << std::endl;
    // We first check who won ("ATTACKER", "DEFENDER", "NOONE")
    QString whoWon;
    deserializationStream >> whoWon;

    // If whoWon was NOONE, then both monsters got destroyed
    if(whoWon == QString::fromStdString("NOONE"))
        std::cout << "No one wins!" << std::endl;
    else if(whoWon == QString::fromStdString("ATTACKER"))
    {
        QString defenderCardName;
        qint32 defenderZoneNumber;

        deserializationStream >> defenderCardName
                              >> defenderZoneNumber;

        std::cout << "The attacker wins!" << std::endl;

        // TODO: get a pointer to the defender
        // TODO: currentPlayer->destroyMonster(defender)
    }
    else
        std::cout << "The defender wins!" << std::endl;

    // Notify the server that deserialization is finished
    notifyServerThatDeserializationHasFinished();
}

void Game::deserializeLpChange(QDataStream &deserializationStream)
{
    std::cout << "We are in deserializeLpChange" << std::endl;

    // We need to check whose life points got changed
    QString whoseLifePointsChanged;
    qint32 newLifePoints;

    deserializationStream >> whoseLifePointsChanged
                          >> newLifePoints;

    // Now we need to actually set the targeted player's lp to newLifePoints
    if (whoseLifePointsChanged.toStdString() == GameExternVars::pCurrentPlayer->getPlayerName())
    {
        GameExternVars::pCurrentPlayer->setPlayerLifePoints(newLifePoints);
        ui->labelCurrentPlayerLpDynamic->setText(QString::fromStdString(std::to_string(GameExternVars::pCurrentPlayer->getPlayerLifePoints())));
    }
    else
    {
        GameExternVars::pOtherPlayer->setPlayerLifePoints(newLifePoints);
        ui->labelOtherPlayerLpDynamic->setText(QString::fromStdString(std::to_string(GameExternVars::pOtherPlayer->getPlayerLifePoints())));
    }

    // Notify the server that deserialization is finished
    notifyServerThatDeserializationHasFinished();
}

void Game::deserializeDeserializationFinished(QDataStream &deserializationStream)
{
    emit deserializationFinished();


//    QTimer::singleShot(0, this, &Game::deserializationFinished);
}

void Game::deserializeGamePhaseChanged(QDataStream &deserializationStream)
{
    // Read the new game phase
    QString currentGamePhaseQString;
    deserializationStream >> currentGamePhaseQString;

    // Update extern var and label
    GamePhaseExternVars::currentGamePhase = GamePhaseExternVars::QStringToGamePhase.at(currentGamePhaseQString);
    ui->labelGamePhase->setText(currentGamePhaseQString);


    // Notify the server that deserialization is finished
    notifyServerThatDeserializationHasFinished();
}

void Game::deserializeNewTurn(QDataStream &deserializationStream)
{
    // We need to read the id of client that will play now
    qint32 newTurnClientID;
    deserializationStream >> newTurnClientID;

    // Switch pointers for this client too.
        /* TODO: This can be a separate function since same code is used in switchPlayers(),
                 yet we can't call switchPlayers because we don't want to send a NEW_TURN header */
    Player *tmp = GameExternVars::pCurrentPlayer;
    GameExternVars::pCurrentPlayer = GameExternVars::pOtherPlayer;
    GameExternVars::pOtherPlayer = tmp;

    std::cout << "Current player is: " << *GameExternVars::pCurrentPlayer << std::endl;
    ui->labelCurrentPlayerNameDynamic->setText(QString::fromStdString(GameExternVars::pCurrentPlayer->getPlayerName()));
    ui->labelOtherPlayerNameDynamic->setText(QString::fromStdString(GameExternVars::pOtherPlayer->getPlayerName()));

    // Update currentTurnClientID
    GameExternVars::currentTurnClientID = newTurnClientID;

    // Reset/Reenable his buttons:
    ui->btnBattlePhase->setEnabled(true);
    ui->btnMainPhase2->setEnabled(false);
    ui->btnEndPhase->setEnabled(true);

    // Notify the server that deserialization is finished
    notifyServerThatDeserializationHasFinished();
}

void Game::deserializeEffectActivated(QDataStream &deserializationStream)
{
    // Get the name of the opponent's card that activated the effect
    QString cardName;
    deserializationStream >> cardName;


    /* TODO: We can't just create an EffectActivator here and use activateEffect(cardName). There are problems with that:
     * 1) What if the effect includes some kind of user input? We can't let this client act like he activated the effect
     * 2) ...
     *
     * It's probably better if we have the consequences of the effect activations sent here and then just apply them.
     */

    std::cout << "PLACEHOLDER COUT: The opponent has activated " << cardName.toStdString() << "'s effect." << std::endl;

    // Notify the server that deserialization is finished
    notifyServerThatDeserializationHasFinished();
}

void Game::deserializeReposition(QDataStream &deserializationStream)
{
    QString cardName;
    qint32 zoneNumber;
    deserializationStream >> cardName
                          >> zoneNumber;

    Card* targetCard = GameExternVars::pCurrentPlayer->field.monsterZone.m_monsterZone[zoneNumber - 1]->m_pCard;

    // We know that its a monster
    MonsterCard *targetMonster = static_cast<MonsterCard *>(targetCard);

    // Change its position
    targetMonster->changePosition();

    // Notify the server that deserialization is finished
    notifyServerThatDeserializationHasFinished();
}

void Game::deserializeDestroyCard(QDataStream &deserializationStream)
{
    QString whoOwnedTheDestroyedCardQString;
    QString cardType;
    qint32 zoneNumber;

    deserializationStream >> whoOwnedTheDestroyedCardQString
                          >> cardType
                          >> zoneNumber;

    // Check who owned the destroyed card
    Player *pPlayerWhoOwnedTheDestroyedCard = nullptr;

    whoOwnedTheDestroyedCardQString == "CURRENT_PLAYER"
        ? pPlayerWhoOwnedTheDestroyedCard = GameExternVars::pCurrentPlayer
        : pPlayerWhoOwnedTheDestroyedCard = GameExternVars::pOtherPlayer;

    // Find the zone that holds the destroyed card
    Zone *pZoneOfTheDestroyedCard = findZone(zoneNumber, cardType, pPlayerWhoOwnedTheDestroyedCard);
    Card *pDestroyedCard = pZoneOfTheDestroyedCard->m_pCard;

    // Actually destroy it
    pPlayerWhoOwnedTheDestroyedCard->sendToGraveyard(*pDestroyedCard, pZoneOfTheDestroyedCard); // TODO: Change all other occurences and add zone parameter

    notifyServerThatDeserializationHasFinished();
}

void Game::onGameStart(qint32 firstToPlay, qint32 clientID)
{
    std::cout << "Game has started!" << std::endl;

    std::cout << "First one to play is client with id " << firstToPlay << std::endl;


    // Set up pointers to current and other player
    if (firstToPlay == 1)
    {
      GameExternVars::pCurrentPlayer = &m_player1;
      GameExternVars::pOtherPlayer = &m_player2;
    }
    else
    {
      GameExternVars::pCurrentPlayer = &m_player2;
      GameExternVars::pOtherPlayer = &m_player1;
    }

    // Set the m_clientID to clientID so we always know who we are
    m_clientID = clientID;

    GameExternVars::currentTurnClientID = firstToPlay;

    // We always want to have our field on the bottom, not current player's.
    int flagBottomField, flagUpperField;
    if(m_clientID == firstToPlay)
    {
        flagBottomField = 1;
        flagUpperField = 2;
    }
    else
    {
        flagBottomField = 2;
        flagUpperField  = 1;
    }


    GameExternVars::pCurrentPlayer->field.setField(flagBottomField, m_viewAndSceneWidth, m_windowHeight);
    for(auto zone : GameExternVars::pCurrentPlayer->field.monsterZone.m_monsterZone) {
        connect(zone, &Zone::zoneRedAndClicked, this, &Game::onRedZoneClick);
        connect(zone, &Zone::zoneGreenAndClicked, this, &Game::onGreenZoneClick);
        ui->graphicsView->scene()->addItem(zone);
    }
    for(auto zone : GameExternVars::pCurrentPlayer->field.spellTrapZone.m_spellTrapZone) {
        connect(zone, &Zone::zoneRedAndClicked, this, &Game::onRedZoneClick);
        connect(zone, &Zone::zoneGreenAndClicked, this, &Game::onGreenZoneClick);
        ui->graphicsView->scene()->addItem(zone);
    }
    for(auto c : GameExternVars::pCurrentPlayer->field.deck.uiDeck) {
        ui->graphicsView->scene()->addItem(c);
    }
    ui->graphicsView->scene()->addItem(GameExternVars::pCurrentPlayer->field.graveyard);
    ui->graphicsView->scene()->addItem(GameExternVars::pCurrentPlayer->field.fieldZone);

    GameExternVars::pOtherPlayer->field.setField(flagUpperField, m_viewAndSceneWidth,m_windowHeight);
    for(auto zone : GameExternVars::pOtherPlayer->field.monsterZone.m_monsterZone) {
        connect(zone, &Zone::zoneRedAndClicked, this, &Game::onRedZoneClick);
        connect(zone, &Zone::zoneGreenAndClicked, this, &Game::onGreenZoneClick);
        ui->graphicsView->scene()->addItem(zone);
    }
    for(auto zone : GameExternVars::pOtherPlayer->field.spellTrapZone.m_spellTrapZone) {
        connect(zone, &Zone::zoneRedAndClicked, this, &Game::onRedZoneClick);
        connect(zone, &Zone::zoneGreenAndClicked, this, &Game::onGreenZoneClick);
        ui->graphicsView->scene()->addItem(zone);
    }
    for(auto c : GameExternVars::pOtherPlayer->field.deck.uiDeck) {
        ui->graphicsView->scene()->addItem(c);
    }
    ui->graphicsView->scene()->addItem(GameExternVars::pOtherPlayer->field.graveyard);
    ui->graphicsView->scene()->addItem(GameExternVars::pOtherPlayer->field.fieldZone);

    // First turn setup at the beginning of the game:
    firstTurnSetup(firstToPlay, clientID, m_viewAndSceneWidth, m_windowHeight);
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

    QString currentGamePhase = GamePhaseExternVars::gamePhaseToQString.at(GamePhaseExternVars::currentGamePhase);
    std::cout << "Current game phase in onGamePhaseChange: " << currentGamePhase.toStdString() << std::endl;
    // Notify the server that the game phase has changed:
    QEventLoop blockingLoop;
    connect(this, &Game::deserializationFinished, &blockingLoop, &QEventLoop::quit);
    QByteArray buffer;
    QDataStream outDataStream(&buffer, QIODevice::WriteOnly);
    outDataStream.setVersion(QDataStream::Qt_5_15);
    outDataStream << QString::fromStdString("GAMEPHASE_CHANGED")
                  << currentGamePhase;
    sendDataToServer(buffer);
    blockingLoop.exec();
}


/* This is actually a slot that does things at the beginning of a new turn
   so it could be called beginNewTurn or onNewTurn or something like that...*/
void Game::onTurnEnd() {
    // Switch the players:
    switchPlayers();

    // Disable the buttons for client that isn't playing this turn
    if(m_clientID != GameExternVars::currentTurnClientID)
    {
        this->ui->btnBattlePhase->setEnabled(false);
        this->ui->btnEndPhase->setEnabled(false);
    }

    // The draw phase begins (this is not optional).
    // There is no need for blockingLoop here since its in onGamePhaseChange()
    GamePhaseExternVars::currentGamePhase = GamePhases::DRAW_PHASE;
    emit gamePhaseChanged(GamePhaseExternVars::currentGamePhase);

    // The current player draws a card (this is not optional).
    GameExternVars::pCurrentPlayer->drawCards(1);

    // Notify the server
    QEventLoop blockingLoop;
    connect(this, &Game::deserializationFinished, &blockingLoop, &QEventLoop::quit);
    QByteArray buffer;
    QDataStream outDataStream(&buffer, QIODevice::WriteOnly);
    outDataStream.setVersion(QDataStream::Qt_5_15);
    outDataStream << QString::fromStdString("ADD_CARD_TO_HAND")
                  << qint32(1)
                  << QString::fromStdString("CURRENT_PLAYER");
    sendDataToServer(buffer);
    blockingLoop.exec();



    // The draw phase ends and the standby phase begins (this is not optional).
    GamePhaseExternVars::currentGamePhase = GamePhases::STANDBY_PHASE;
    emit gamePhaseChanged(GamePhaseExternVars::currentGamePhase);

    /* ... Something may happen here due to effects (maybe we should call checkEffects()
     or something similar that will check if there are effects to be activated in SP */

    // The standby phase ends and the main phase 1 begins (this is not optional).
    GamePhaseExternVars::currentGamePhase = GamePhases::MAIN_PHASE1;
    emit gamePhaseChanged(GamePhaseExternVars::currentGamePhase);

    // Main Phase 1 runs until user clicks one of the buttons.
}

void Game::onCardAddedToScene(Card *card)
{
    connect(card, &Card::cardSelected, this, &Game::onCardSelect);
    connect(card, &Card::cardHoveredEnter, this, &Game::onCardHoverEnter);
    connect(card, &Card::cardHoveredLeave, this, &Game::onCardHoverLeave);

    // Card menu connects
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

    connect(card->cardMenu->repositionButton, &QPushButton::clicked, this, [this, card](){
        onRepositionButtonClick(*card);
    });

    connect(card->cardMenu->attackDirectlyButton, &QPushButton::clicked, this, [this, card]() {
        onAttackDirectlyButtonClick(*card);
    });

    // By default we don't want to show card info unless the card is hovered
    ui->labelImage->setVisible(false);
    ui->textBrowserEffect->setVisible(false);
}

void Game::onCardDraw(Card *pDrawnCard)
{
    ui->graphicsView->scene()->addItem(pDrawnCard);
    ui->graphicsView->scene()->addWidget(pDrawnCard->cardMenu);
    pDrawnCard->cardMenu->setVisible(false);
    emit cardAddedToScene(pDrawnCard);
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
        // std::cout << "New main window width/height: " << m_windowWidth << " / " << m_windowHeight << std::endl;

        // GraphicsView and GraphicsScene adjustments:
        this->setWindowTitle("Yu-Gi-Oh!");
        ui->graphicsView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        ui->graphicsView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

        // We need to calculate other UI sizes so we know what QGraphicsView's size needs to be.
        // TODO: Change leftVerticalLayout name to something normal
        const int leftVerticalLayoutWidth = ui->leftVerticalLayout->sizeHint().width();

        m_viewAndSceneWidth = m_windowWidth - (leftVerticalLayoutWidth);
        ui->graphicsView->setFixedSize(m_viewAndSceneWidth, m_windowHeight);
        ui->graphicsView->scene()->setSceneRect(0, 0, m_viewAndSceneWidth, m_windowHeight);

        // TODO: Check if this is needed
        ui->graphicsView->fitInView(0, 0, m_viewAndSceneWidth, m_windowHeight, Qt::KeepAspectRatio);

        QPixmap background(":/resources/pictures/space.jpeg");
        background = background.scaled(m_viewAndSceneWidth,  this->size().height(), Qt::IgnoreAspectRatio);
        QBrush brush(QPalette::Window, background);
        ui->graphicsView->setBackgroundBrush(brush);
    }
}

void Game::onCardHoverEnter(Card &card)
{
    std::cout << "Card " << card.getCardName() << " hover-entered!" << std::endl;

    /* If the card is a monster, we want its ATK/DEF in card description too.
     * If its not a monster, it will be empty string and won't mess with the description. */
    std::string atkDefIfMonster = "";
    if(card.getCardType() == CardType::MONSTER_CARD)
    {
        MonsterCard *monsterCard = static_cast<MonsterCard *>(&card);
        atkDefIfMonster += "ATK: " + std::to_string(monsterCard->getAttackPoints()) + "  /  DEF: " + std::to_string(monsterCard->getDefensePoints());
    }

    // Set the correct card image
    QPixmap pix;
    pix.load(QString::fromStdString(card.imagePath));
    pix = pix.scaled(ui->labelImage->size(), Qt::KeepAspectRatio);
    ui->labelImage->setPixmap(pix);

    // Set the description text
    ui->textBrowserEffect->setText(QString::fromStdString(
                                                            card.getCardDescription() + "\n\n\n\n"
                                                            + atkDefIfMonster
                                                         ));

    // Enable card info ui
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
    card->setCardMenu();

    // We need to check if the opponent has any monsters. If he doesn't, we don't show Attack Directly button
    !GameExternVars::pOtherPlayer->field.monsterZone.isEmpty()
         ? card->cardMenu->attackDirectlyButton->setVisible(false)
         : card->cardMenu->attackDirectlyButton->setVisible(true);

    // We only want current client to be able to have a card menu
        // TODO: Should this be at the beginning of this function?
    if(m_clientID == GameExternVars::currentTurnClientID)
        card->cardMenu->isVisible() == false ? card->cardMenu->show() : card->cardMenu->hide();
}



// Slots for card menu UI
void Game::onActivateButtonClick(Card &card)
{
    std::cout << "Activate button clicked on card " << card.getCardName() << std::endl;

    // Idea: Map of function pointers for effects
    const std::string cardName = card.getCardName();

    // Effect activator is needed for effect handling
    EffectActivator effectActivator(card);

    // We connect every signal from EffectActivator to our slots in Game:
    connect(&effectActivator, &EffectActivator::lifePointsChanged, this, &Game::onLifePointsChange);
    connect(&effectActivator, &EffectActivator::gameEnded, this, &Game::onGameEnd);

    // Notify the server / other client
    QEventLoop blockingLoop;
    connect(this, &Game::deserializationFinished, &blockingLoop, &QEventLoop::quit);
    QByteArray buffer;
    QDataStream outDataStream(&buffer, QIODevice::WriteOnly);
    outDataStream.setVersion(QDataStream::Qt_5_15);
    outDataStream << QString::fromStdString("EFFECT_ACTIVATED")
                  << QString::fromStdString(cardName); // Who activated the effect
    sendDataToServer(buffer);
    blockingLoop.exec();

    // Activate the actual effect. We need to block in case the effects triggers another header, like LP_CHANGE for example
    QEventLoop blockingLoop2;
    connect(this, &Game::deserializationFinished, &blockingLoop2, &QEventLoop::quit);
    effectActivator.activateEffect(cardName);
    blockingLoop2.exec();
}

void Game::onSummonButtonClick(Card &card) {
    std::cout<< "Summon button was clicked on card " << card.getCardName() << std::endl;

    // Remove target card from player's hand
    GameExternVars::pCurrentPlayer->m_hand.removeFromHand(card);



    /* Set this card that is to-be-summoned to a global summon target, in order for Zone objects to be able
       to see it. */
    GameExternVars::pCardToBePlacedOnField = &card;
    std::cout << "Current summon target is: " << GameExternVars::pCardToBePlacedOnField->getCardName() << std::endl;

    // Set the monster's position explicitly to ATTACK (since thats the only one allowed when summoning)
    MonsterCard *monsterCard = static_cast<MonsterCard *>(&card);
    monsterCard->setPosition(MonsterPosition::ATTACK);

    // Color the free zones so user can select one to place.
    GameExternVars::pCurrentPlayer->field.monsterZone.colorFreeZones();
}

void Game::onAttackButtonClick(Card &attackingMonster)
{
   std::cout << "Attack button clicked" << std::endl;

   // Set the monster that initiated the attack as the global attacking monster
   GameExternVars::pAttackingMonster = &attackingMonster;

   // Color opponent's monsters
   GameExternVars::pOtherPlayer->field.monsterZone.colorOccupiedZones();
}

void Game::onRepositionButtonClick(Card &card)
{
    std::cout << "Reposition button clicked for card " << card.getCardName() << std::endl;

    // We are sure that this card is a MonsterCard since only monsters can change their position to defense or attack
    MonsterCard *monsterCard = static_cast<MonsterCard *>(&card);

    // Change the position
    monsterCard->changePosition();

    // Find the zone number
    qint32 zoneNumber = findZoneNumber(*monsterCard, GameExternVars::pCurrentPlayer);

    // Notify the server / other client
    QEventLoop blockingLoop;
    connect(this, &Game::deserializationFinished, &blockingLoop, &QEventLoop::quit);
    QByteArray buffer;
    QDataStream outDataStream(&buffer, QIODevice::WriteOnly);
    outDataStream.setVersion(QDataStream::Qt_5_15);
    outDataStream << QString::fromStdString("REPOSITION")
                  << QString::fromStdString(monsterCard->getCardName()) // TODO: This is maybe unneeded, since we can locate the monster by just using the zone number
                  << zoneNumber; // Zone number, so we can locate the monster
    sendDataToServer(buffer);
    blockingLoop.exec();
}

void Game::onAttackDirectlyButtonClick(Card &card)
{
    MonsterCard *monsterCard = static_cast<MonsterCard *>(&card);
    damagePlayer(*GameExternVars::pOtherPlayer, monsterCard->getAttackPoints());
}


/* TODO: This should accept the targetPlayer as an argument, because otherwise we always print currentPlayer's hp,
         even if it was other player's health that had changed. */
void Game::onLifePointsChange(Player &targetPlayer) // const?
{
    std::cout << "Current health points for player " << targetPlayer.getPlayerName() << " : "<< targetPlayer.getPlayerLifePoints() << std::endl;

    // Update labels
    ui->labelCurrentPlayerLpDynamic->setText(QString::fromStdString(std::to_string(GameExternVars::pCurrentPlayer->getPlayerLifePoints())));
    ui->labelOtherPlayerLpDynamic->setText(QString::fromStdString(std::to_string(GameExternVars::pOtherPlayer->getPlayerLifePoints())));


    // Notify the server about health change.
    QEventLoop blockingLoop;
    connect(this, &Game::deserializationFinished, &blockingLoop, &QEventLoop::quit);
    QByteArray buffer;
    QDataStream outDataStream(&buffer, QIODevice::WriteOnly);
    outDataStream.setVersion(QDataStream::Qt_5_15);
    outDataStream << QString::fromStdString("LP_CHANGE")
                  << QString::fromStdString(targetPlayer.getPlayerName()) // Whose life points has changed
                  << qint32(targetPlayer.getPlayerLifePoints()); // New life points
    sendDataToServer(buffer);
    blockingLoop.exec();
}

void Game::onGameEnd(Player &loser)
{
    loser.setPlayerLifePoints(0);
    ui->labelCurrentPlayerLpDynamic->setText(QString::fromStdString(std::to_string(GameExternVars::pCurrentPlayer->getPlayerLifePoints())));
    ui->labelOtherPlayerLpDynamic->setText(QString::fromStdString(std::to_string(GameExternVars::pOtherPlayer->getPlayerLifePoints())));
    std::cout << "The game has ended! Player " << loser.getPlayerName() << " has lost because his health points reached 0 !" << std::endl;

    // Notify the server
    QEventLoop blockingLoop;
    connect(this, &Game::deserializationFinished, &blockingLoop, &QEventLoop::quit);
    QByteArray buffer;
    QDataStream outDataStream(&buffer, QIODevice::WriteOnly);
    outDataStream.setVersion(QDataStream::Qt_5_15);
    outDataStream << QString::fromStdString("LP_CHANGE")
                  << QString::fromStdString(loser.getPlayerName()) // Whose life points has changed
                  << qint32(0); // New life points
    sendDataToServer(buffer);
    blockingLoop.exec();

    // TODO: Stop the game here (or maybe in the server too) somehow!
}

void Game::onSetButtonClick(Card &card)
{
    std::cout << "Set button clicked on card " << card.getCardName() << std::endl;

    // Remove target card from player's hand
    GameExternVars::pCurrentPlayer->m_hand.removeFromHand(card);

    /* Set this card that is to-be-summoned to a global summon target, in order for Zone objects to be able
       to see it. */
    GameExternVars::pCardToBePlacedOnField = &card;
    std::cout << "Current Set target is: " << GameExternVars::pCardToBePlacedOnField->getCardName() << std::endl;


    /* Since both spells/traps and monsters can be Set (but the behavior differs!),
       we need to see what this card actually is. */

    if(card.getCardType() == CardType::MONSTER_CARD)
    {
        MonsterCard *monsterCard = static_cast<MonsterCard *>(&card);

        // Set its position to FACE_DOWN_DEFENSE
        monsterCard->setPosition(MonsterPosition::FACE_DOWN_DEFENSE);

        GameExternVars::pCurrentPlayer->field.monsterZone.colorFreeZones();
    }
    else if(card.getCardType() == CardType::SPELL_CARD)
    {
       SpellCard *spellCard = static_cast<SpellCard *>(&card);

       // Set its position to SET
       spellCard->setPosition(SpellTrapPosition::SET);

       GameExternVars::pCurrentPlayer->field.spellTrapZone.colorFreeZones();
    }
    else
    {
        TrapCard *trapCard = static_cast<TrapCard *>(&card);
        trapCard->setPosition(SpellTrapPosition::SET);
        GameExternVars::pCurrentPlayer->field.spellTrapZone.colorFreeZones();
    }

}


// TODO: summonAlready = true , activatedAlready = true at the end of onRedZoneClick?
void Game::onRedZoneClick(Zone *clickedRedZone)
{
    Card *card = GameExternVars::pCardToBePlacedOnField;
    std::cout << "Card " << *card << std::endl;

    // TODO: Move these into separate functions.
    if(card->getCardType() == CardType::MONSTER_CARD)
    {
        GameExternVars::pCurrentPlayer->field.monsterZone.placeInMonsterZone(card, clickedRedZone);
        card->setCardLocation(CardLocation::FIELD);

        // Read the monster's position
        MonsterCard *pMonsterCard = static_cast<MonsterCard *>(card);
        QString monsterPosition = pMonsterCard->monsterPositionEnumToQString.at(pMonsterCard->getPosition());

        // If the position is SET, we need to rotate the card and change the pixmap to card_back.jpg
        if(monsterPosition == QString::fromStdString("FACE_DOWN_DEFENSE"))
            visuallySetMonster(pMonsterCard);

        GameExternVars::pCurrentPlayer->field.monsterZone.refresh();

        // Find the zone number
        qint32 zoneNumber = findZoneNumber(*card, GameExternVars::pCurrentPlayer);

        QEventLoop blockingLoop;
        connect(this, &Game::deserializationFinished, &blockingLoop, &QEventLoop::quit);
        QByteArray buffer;
        QDataStream outDataStream(&buffer, QIODevice::WriteOnly);
        outDataStream.setVersion(QDataStream::Qt_5_15);
        outDataStream << QString("FIELD_PLACEMENT") // Header, so that server knows what data to expect after it
                      << QString::fromStdString(card->getCardName()) // We only send card's name, server will pass it to the other client and then that client will construct the card
                      << QString::fromStdString(card->getCardTypeString())
                      << zoneNumber
                      << monsterPosition;
        sendDataToServer(buffer);
        blockingLoop.exec();


        // Set this monster's summon flag to true
        pMonsterCard->setAlreadySummonedThisTurn(true);
    }
    else if(card->getCardType() == CardType::SPELL_CARD || card->getCardType() == CardType::TRAP_CARD) {
        GameExternVars::pCurrentPlayer->field.spellTrapZone.placeInSpellTrapZone(card, clickedRedZone);
        card->setCardLocation(CardLocation::FIELD);
        for(auto x : GameExternVars::pCurrentPlayer->field.spellTrapZone.m_spellTrapZone) {
            if(!x->isEmpty())
                std::cout << *x->m_pCard << std::endl;
        }
        GameExternVars::pCurrentPlayer->field.spellTrapZone.refresh();


        // Get the spell/trap's position
        QString spellTrapPosition;
        if(card->getCardType() == CardType::SPELL_CARD)
        {
            SpellCard *pSpellCard = static_cast<SpellCard *>(card);
            spellTrapPosition = pSpellCard->spellTrapPositionEnumToQString.at(pSpellCard->getSpellPosition());

            if(spellTrapPosition == QString::fromStdString("SET"))
                visuallySetSpell(pSpellCard);
        }
        else
        {
            TrapCard *pTrapCard = static_cast<TrapCard *>(card);
            spellTrapPosition = pTrapCard->spellTrapPositionEnumToQString.at(pTrapCard->getTrapPosition());

            if(spellTrapPosition == QString::fromStdString("SET"))
                visuallySetTrap(pTrapCard);
        }

        qint32 zoneNumber = findZoneNumber(*card, GameExternVars::pCurrentPlayer);

        QEventLoop blockingLoop;
        connect(this, &Game::deserializationFinished, &blockingLoop, &QEventLoop::quit);
        QByteArray buffer;
        QDataStream outDataStream(&buffer, QIODevice::WriteOnly);
        outDataStream.setVersion(QDataStream::Qt_5_15);

        outDataStream << QString("FIELD_PLACEMENT")
                      << QString::fromStdString(card->getCardName())
                      << QString::fromStdString(card->getCardTypeString())
                      << zoneNumber
                      << spellTrapPosition;
        sendDataToServer(buffer);
        blockingLoop.exec();
    }
}

void Game::onGreenZoneClick(Zone *clickedGreenZone) {
    std::cout << "Green zone was clicked!" << std::endl;

    // Disable attack button for the attacker
    GameExternVars::pAttackingMonster->cardMenu->attackButton->setVisible(false);


    // TODO: MonsterCard instead of Card?
    Card* attackedMonster = clickedGreenZone->m_pCard;

    // Refresh the opponent's monster zone
    GameExternVars::pOtherPlayer->field.monsterZone.refresh();

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

    //First we need to check what header we have
    QString header;
    m_inDataStream >> header;

    std::cout << "Header: " << header.toStdString() << std::endl;

    if(!m_inDataStream.commitTransaction())
        return;

    m_currentHeader = header;

    // Then we call the appropriate deserialization method for that header:
    auto deserializationFunctionPointer = m_deserializationMap.at(m_currentHeader);
    (this->*deserializationFunctionPointer)(m_inDataStream);
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
    std::cout << "Current player draws 5 - not actually, this is a test" << std::endl;
    QEventLoop blockingLoop;
    connect(this, &Game::deserializationFinished, &blockingLoop, &QEventLoop::quit);
    QByteArray buffer;
    QDataStream outDataStream(&buffer, QIODevice::WriteOnly);
    outDataStream.setVersion(QDataStream::Qt_5_15);

    outDataStream << QString::fromStdString("ADD_CARD_TO_HAND")
                  << qint32(5)
                  << QString::fromStdString("CURRENT_PLAYER");

   if(!sendDataToServer(buffer))
    {
       std::cerr << "Error in sendDataToServer function! " << std::endl;
       return;
   }

   blockingLoop.exec();
}

int Game::getLifePointsJson(){
    QString val;
    QFile file;
    file.setFileName(":/resources/deck_settings.json");
    file.open(QIODevice::ReadOnly | QIODevice::Text);
    val = file.readAll();
    file.close();
    QJsonDocument d = QJsonDocument::fromJson(val.toUtf8());
    QJsonObject obj = d.object();

    int lifePoints = d["lifepoints"].toInt();
    return lifePoints;
}

int Game::getNumberOfCardsJson(){
    QString val;
    QFile file;
    file.setFileName(":/resources/deck_settings.json");
    file.open(QIODevice::ReadOnly | QIODevice::Text);
    val = file.readAll();
    file.close();
    QJsonDocument d = QJsonDocument::fromJson(val.toUtf8());
    QJsonObject obj = d.object();

    int numberOfCards = d["numberofcards"].toInt();
    return numberOfCards;
}

int Game::getTimePerMoveJson(){
    QString val;
    QFile file;
    file.setFileName(":/resources/deck_settings.json");
    file.open(QIODevice::ReadOnly | QIODevice::Text);
    val = file.readAll();
    file.close();
    QJsonDocument d = QJsonDocument::fromJson(val.toUtf8());
    QJsonObject obj = d.object();

    int timePerMove = d["timepermove"].toInt();
    return timePerMove;
}
