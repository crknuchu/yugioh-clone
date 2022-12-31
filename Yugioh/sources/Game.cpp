#include "headers/ui_mainwindow.h"
#include "headers/Game.h"
#include "headers/Monstercard.h"
#include "headers/EffectActivator.h"
#include "headers/EffectRequirement.h"
#include "headers/MonsterZone.h"
#include "headers/SpellTrapZone.h"
#include "headers/Serializer.h"
#include "headers/Field.h"
#include "headers/Hand.h"
#include "sources/profilesettings.h"

#include <iostream>

#include <map>
#include <functional>

#include <QGraphicsScene>
#include <QGraphicsLayout>
#include <QMessageBox>
#include <QTimer>
#include <QDebug>

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
    {"LP_CHANGE",                                       &Game::deserializeLpChange},
    {"DESERIALIZATION_FINISHED",                        &Game::deserializeDeserializationFinished},
    {"GAMEPHASE_CHANGED",                               &Game::deserializeGamePhaseChanged},
    {"NEW_TURN",                                        &Game::deserializeNewTurn},
    {"EFFECT_ACTIVATED",                                &Game::deserializeEffectActivated},
    {"REPOSITION",                                      &Game::deserializeReposition},
    {"FLIP",                                            &Game::deserializeFlip},
    {"DESTROY_CARD",                                    &Game::deserializeDestroyCard},
    {"GAME_END",                                        &Game::deserializeGameEnd}
};

bool MonsterCard::globalSummonedThisTurn = false;
Card *GameExternVars::pCardToBeReturned = nullptr;

void delay()
{
    QTime dieTime= QTime::currentTime().addSecs(1);
    while (QTime::currentTime() < dieTime)
        QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
}

Game::Game(Player p1, Player p2, int lifePoints, int numberOfCards, int timePerMove, QWidget *parent )
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

    ui->progressBar->hide();
    ui->enemyPoints->hide();
    ui->avatarPlayer->hide();
    ui->enemyAvatar->hide();
    ui->enemyName->hide();
    ui->namePlayer->hide();
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
    //     // TODO: Kaiba.json
    // Serializer s;
    // s.loadFromJson(":/resources/yugi.json");
    // GameExternVars::yugiCards = s.getCards();
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
    qint32 defenderZoneNumber = findZoneNumber(defender, GameExternVars::pOtherPlayer);

    if(defender.getPosition() == MonsterPosition::FACE_DOWN_DEFENSE) {
         visuallyFlipMonster(&defender, -180);
         defender.setPosition(MonsterPosition::FACE_UP_DEFENSE);

         QEventLoop blockingLoop1;
         connect(this, &Game::deserializationFinished, &blockingLoop1, &QEventLoop::quit);
         QByteArray buffer1;
         QDataStream outDataStream1(&buffer1, QIODevice::WriteOnly);
         outDataStream1.setVersion(QDataStream::Qt_5_15);
         outDataStream1 << QString::fromStdString("FLIP")
                       << QString::fromStdString("OTHER_PLAYER")
                       << QString::fromStdString(defender.getCardName()) // TODO: This is maybe unneeded, since we can locate the monster by just using the zone number
                       << defenderZoneNumber; // Zone number, so we can locate the monster
         sendDataToServer(buffer1);
         blockingLoop1.exec();

         EffectRequirement effectRequirement(defender);
         bool cardActivationReq = effectRequirement.isActivatable(defender.getCardName());
         if(cardActivationReq) {
            EffectActivator effectActivator(defender);
            effectActivator.activateEffect(defender.getCardName(),  false);

            QEventLoop blockingLoop2;
            connect(this, &Game::deserializationFinished, &blockingLoop2, &QEventLoop::quit);
            QByteArray buffer2;
            QDataStream outDataStream2(&buffer2, QIODevice::WriteOnly);
            outDataStream2.setVersion(QDataStream::Qt_5_15);
            outDataStream2 << QString::fromStdString("EFFECT_ACTIVATED")
                           << QString::fromStdString("OTHER_PLAYER")
                           << QString::fromStdString(defender.getCardName()) // Who activated the effect
                           << QString::fromStdString(defender.getCardTypeString())
                           << defenderZoneNumber;

            sendDataToServer(buffer2);
            blockingLoop2.exec();
         }
    }

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

        // Flip the destroyed monster if it was in FACE_DOWN_DEFENSE position

        // We need the destroyed monster's zone number
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
    if(pMonsterCard->getPosition() == MonsterPosition::FACE_DOWN_DEFENSE) {
        pix.load(":/resources/pictures/card_back.jpg");
        pix = pix.scaled(QSize(pMonsterCard->width, pMonsterCard->height), Qt::KeepAspectRatio);
    }
    QTransform transformationMatrix;
    transformationMatrix.rotate(90);
    pMonsterCard->setPixmap(pix.transformed(transformationMatrix));

    pMonsterCard->move(pMonsterCard->x() - pMonsterCard->width / 5 , pMonsterCard->y() + pMonsterCard->height / 5 );
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

void Game::visuallyFlipMonster(MonsterCard *pMonsterCard, qreal degrees)
{
    pMonsterCard->move(pMonsterCard->x() + pMonsterCard->width / 5 , pMonsterCard->y() - pMonsterCard->height / 5 );

    QTransform transformationMatrix;
    transformationMatrix.rotate(degrees);
    QPixmap pix;
    pix.load(QString::fromStdString(pMonsterCard->imagePath));
    pix = pix.scaled(QSize(pMonsterCard->width, pMonsterCard->height), Qt::KeepAspectRatio);
    pMonsterCard->setPixmap(pix.transformed(transformationMatrix));


}

void Game::visuallyFlipSpell(SpellCard *pSpellCard)
{
    // FIXME: We can't use this for both flipping our and opponent's cards, since our cards will be rotated by 180 degress which is something we don't want to do.
    QPixmap pix;
    pix.load(QString::fromStdString(pSpellCard->imagePath));
    pix = pix.scaled(QSize(pSpellCard->width, pSpellCard->height), Qt::KeepAspectRatio);
    pSpellCard->setPixmap(pix);
}

void Game::visuallyFlipTrap(TrapCard *pTrapCard)
{
    // FIXME: We can't use this for both flipping our and opponent's cards, since our cards will be rotated by 180 degress which is something we don't want to do.
    QPixmap pix;
    pix.load(QString::fromStdString(pTrapCard->imagePath));
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

//    ui->labelCurrentPlayerLpDynamic->hide();
//    ui->labelOtherPlayerLpDynamic->hide();
//    ui->labelCurrentPlayerLpConst->hide();
//    ui->labelOtherPlayerLpConst->hide();

    std::cout << "The first one to play is " << GameExternVars::pCurrentPlayer->getPlayerName() << std::endl;
    m_currentTurn = 1;

    GamePhaseExternVars::currentGamePhase = GamePhases::DRAW_PHASE;
    ui->labelGamePhase->setText(QString::fromStdString("DRAW PHASE")); // We hardcode it here since both clients are in sync here

    // The first one gets 6 cards
    GameExternVars::pCurrentPlayer->field.deck.shuffleDeck(1);
    GameExternVars::pCurrentPlayer->drawCards(6);
    // The other one gets 5 cards
    GameExternVars::pOtherPlayer->field.deck.shuffleDeck(2);
    GameExternVars::pOtherPlayer->drawCards(5);


    // We need to make other player's cards have card_back.jpg pixmap
    if(m_clientID == firstToPlay)
    {
        QPixmap cardBackPixmap(":/resources/pictures/card_back.jpg");
        for(Card *card : GameExternVars::pOtherPlayer->m_hand.getHand()) {
            cardBackPixmap = cardBackPixmap.scaled(QSize(card->width, card->height), Qt::KeepAspectRatio);
            card->setPixmap(cardBackPixmap);
        }
    }
    else
    {
        QPixmap cardBackPixmap(":/resources/pictures/card_back.jpg");
        for(Card *card : GameExternVars::pCurrentPlayer->m_hand.getHand()) {
            cardBackPixmap = cardBackPixmap.scaled(QSize(card->width, card->height), Qt::KeepAspectRatio);
            card->setPixmap(cardBackPixmap);
        }
    }

    GamePhaseExternVars::currentGamePhase = GamePhases::STANDBY_PHASE;
    ui->labelGamePhase->setText(QString::fromStdString("STANDBY PHASE"));

    GamePhaseExternVars::currentGamePhase = GamePhases::MAIN_PHASE1;
    ui->labelGamePhase->setText(QString::fromStdString("MAIN PHASE 1"));





    //just a placeholder code for hand
//     MonsterCard* testCard1 = new MonsterCard("Hane-Hane", 450, 500, 4,
//                                               MonsterType::SPELLCASTER, MonsterKind::EFFECT_MONSTER,
//                                               MonsterAttribute::EARTH, false, MonsterPosition::FACE_DOWN_DEFENSE, false,
//                                               CardType::MONSTER_CARD, CardLocation::FIELD,
//                                               "Neither player can target Dragon monsters on the field with card effects.",
//                                               ":/resources/pictures/HaneHane.jpg"
//                                               );
//     MonsterCard* testCard2 = new MonsterCard("Hane-Hane", 450, 500, 4,
//                                               MonsterType::SPELLCASTER, MonsterKind::EFFECT_MONSTER,
//                                               MonsterAttribute::EARTH, false, MonsterPosition::FACE_DOWN_DEFENSE, false,
//                                               CardType::MONSTER_CARD, CardLocation::FIELD,
//                                               "Neither player can target Dragon monsters on the field with card effects.",
//                                               ":/resources/pictures/HaneHane.jpg"
//                                               );

//     MonsterCard* testCard3 = new MonsterCard("Trap Master", 500, 1500, 4,
//                                               MonsterType::SPELLCASTER, MonsterKind::EFFECT_MONSTER,
//                                               MonsterAttribute::DARK, false, MonsterPosition::ATTACK, false,
//                                               CardType::MONSTER_CARD, CardLocation::GRAVEYARD,
//                                               "Neither player can target Dragon monsters on the field with card effects.",
//                                               ":/resources/pictures/TrapMaster.jpg"
//                                               );
//     SpellCard* testCard4 = new SpellCard(SpellType::NORMAL_SPELL, "Card Destruction",
//                                             CardType::SPELL_CARD, CardLocation::HAND, SpellTrapPosition::NONE,
//                                             "  An EARTH monster equipped with this card increases "
//                                             "its ATK by 400 points and decreases its DEF by 200 points.",
//                                             ":/resources/pictures/CardDestruction.jpg", true);

//   emit GameExternVars::pCurrentPlayer->cardAddedToScene(testCard1);
//   emit GameExternVars::pCurrentPlayer->cardAddedToScene(testCard2);
//   emit GameExternVars::pCurrentPlayer->cardAddedToScene(testCard3);
//   emit GameExternVars::pCurrentPlayer->cardAddedToScene(testCard4);

//   //testing purposes
//   GameExternVars::pCurrentPlayer->field.monsterZone.placeInMonsterZone(testCard1, 2);
//   visuallySetMonster(testCard1);
//   GameExternVars::pOtherPlayer->field.monsterZone.placeInMonsterZone(testCard3,2);
//   GameExternVars::pCurrentPlayer->m_hand.addToHand(*testCard2);
//   GameExternVars::pCurrentPlayer->m_hand.addToHand(*testCard4);


  //just a placeholder code for hand
//   MonsterCard* testCard1 = new MonsterCard("Hane-Hane", 450, 500, 4,
//                                               MonsterType::SPELLCASTER, MonsterKind::EFFECT_MONSTER,
//                                               MonsterAttribute::EARTH, false, Position::ATTACK, false,
//                                               CardType::MONSTER_CARD, CardLocation::FIELD,
//                                               "Neither player can target Dragon monsters on the field with card effects.",
//                                               ":/resources/pictures/HaneHane.jpg"
//                                               );
//   SpellCard* testCard2 = new SpellCard(SpellType::NORMAL_SPELL, "Change of Heart",
//                                              CardType::SPELL_CARD, CardLocation::HAND,
//                                              "  Increase your Life Points by 1000 points.  ", ":/resources/pictures/ChangeofHeart.jpg", true);

//   MonsterCard* testCard3 = new MonsterCard("Blue dragon", 3000, 2500, 4,
//                                               MonsterType::SPELLCASTER, MonsterKind::EFFECT_MONSTER,
//                                               MonsterAttribute::DARK, false, Position::ATTACK, false,
//                                               CardType::MONSTER_CARD, CardLocation::GRAVEYARD,
//                                               "Neither player can target Dragon monsters on the field with card effects.",
//                                               ":/resources/pictures/blue_eyes.jpg"
//                                               );
//   SpellCard* testCard4 = new SpellCard(SpellType::NORMAL_SPELL, "Monster Reborn",
//                                              CardType::SPELL_CARD, CardLocation::HAND,
//                                              "  An EARTH monster equipped with this card increases "
//                                              "its ATK by 400 points and decreases its DEF by 200 points.",
//                                        ":/resources/pictures/MonsterReborn.jpg", true);

//   emit GameExternVars::pCurrentPlayer->cardAddedToScene(testCard1);
//   emit GameExternVars::pCurrentPlayer->cardAddedToScene(testCard2);
//   emit GameExternVars::pCurrentPlayer->cardAddedToScene(testCard3);
//   emit GameExternVars::pCurrentPlayer->cardAddedToScene(testCard4);

//   //testing purposes
//   GameExternVars::pCurrentPlayer->field.monsterZone.placeInMonsterZone(testCard1, 2);
//   GameExternVars::pOtherPlayer->field.monsterZone.placeInMonsterZone(testCard3,2);
//   GameExternVars::pCurrentPlayer->m_hand.addToHand(*testCard2);
//   GameExternVars::pCurrentPlayer->m_hand.addToHand(*testCard4);
//  GameExternVars::pCurrentPlayer->field.graveyard->sendToGraveyard(new testCard);
    // Label setup:
    ui->labelCurrentPlayerNameDynamic->setText(QString::fromStdString(GameExternVars::pCurrentPlayer->getPlayerName()));
    ui->labelOtherPlayerNameDynamic->setText(QString::fromStdString(GameExternVars::pOtherPlayer->getPlayerName()));

    ui->labelCurrentPlayerLpDynamic->setText(QString::fromStdString(std::to_string(GameExternVars::pCurrentPlayer->getPlayerLifePoints())));
    ui->labelOtherPlayerLpDynamic->setText(QString::fromStdString(std::to_string(GameExternVars::pOtherPlayer->getPlayerLifePoints())));

    ui->progressBar->setValue(GameExternVars::pCurrentPlayer->getPlayerLifePoints());
    ui->enemyPoints->setValue(GameExternVars::pOtherPlayer->getPlayerLifePoints());

}


// QT related stuff:
void Game::setupConnections() {
    // Game
    connect(this, &Game::mainWindowResized, this, &Game::onMainWindowResize);
    connect(this, &Game::gameStarted, this, &Game::onGameStart);
    connect(this, &Game::gamePhaseChanged, this, &Game::onGamePhaseChange);
    connect(this, &Game::turnEnded, this, &Game::onTurnEnd);
    connect(&m_player1, &Player::cardAddedToScene, this, &Game::onCardAddedToScene);
    connect(&m_player2, &Player::cardAddedToScene, this, &Game::onCardAddedToScene);
    connect(this, &Game::gameEndedAfterBattle, this, &Game::onGameEnd); // Same slot for both game endings (one in EffectActivator and one here)
    connect(this, &Game::lifePointsChanged, this, &Game::onLifePointsChange);
    connect(this, &Game::activateFromHand, this, &Game::onActivateFromHand);

    // Buttons
    connect(ui->btnBattlePhase, &QPushButton::clicked, this, &Game::onBattlePhaseButtonClick);
    connect(ui->btnMainPhase2, &QPushButton::clicked, this, &Game::onMainPhase2ButtonClick);
    connect(ui->btnEndPhase, &QPushButton::clicked, this, &Game::onEndPhaseButtonClick);
    // Networking
    connect(m_pTcpSocket, &QIODevice::readyRead, this, &Game::onDataIncoming);
    connect(m_pTcpSocket, &::QAbstractSocket::errorOccurred, this, &Game::onNetworkErrorOccurred);
    connect(ui->btnConnect, &QPushButton::clicked, this, &Game::onConnectButtonClick);
    connect(ui->btnWriteData, &QPushButton::clicked, this, &Game::onWriteDataButtonClick);

    connect(this, &Game::returnCardToOpponent, this, &Game::onReturnCardToOpponent);

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
    Card* targetCard;
    for(Card* card : GameExternVars::pCurrentPlayer->m_hand.getHand()) {
        if(cardName.toStdString() == card->getCardName())
            targetCard = card;
    }

    for(Card* card : GameExternVars::pCurrentPlayer->field.graveyard->getGraveyard()) {
        if(cardName.toStdString() == card->getCardName())
            targetCard = card;
    }

    // Set the original pixmap
    QPixmap originalPixmap;
    originalPixmap.load(QString::fromStdString(targetCard->imagePath));
    originalPixmap = originalPixmap.scaled(QSize(targetCard->width, targetCard->height), Qt::KeepAspectRatio);
    targetCard->setPixmap(originalPixmap);

    // Add the card to the scene
    GameExternVars::pCurrentPlayer->m_hand.removeFromHand(*targetCard);
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
            if(stPosition == SpellTrapPosition::SET)
                visuallySetSpell(spellCard);
        }
        else
        {
            TrapCard *trapCard = static_cast<TrapCard *>(targetCard);
            stPosition = trapCard->spellTrapPositionQStringToEnum.at(positionQString);
            trapCard->setPosition(stPosition);
            if(stPosition == SpellTrapPosition::SET)
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
    QString whichPlayerActivatedEffect;
    QString cardName;
    QString cardType;
    qint32 zoneNumber;
    deserializationStream >> whichPlayerActivatedEffect
                          >> cardName
                          >> cardType
                          >> zoneNumber;

    Card* targetCard;
    if(whichPlayerActivatedEffect == QString::fromStdString("CURRENT_PLAYER")) {
        cardType == "monster card"
                ? targetCard = GameExternVars::pCurrentPlayer->field.monsterZone.m_monsterZone[zoneNumber - 1]->m_pCard
                : targetCard = GameExternVars::pCurrentPlayer->field.spellTrapZone.m_spellTrapZone[zoneNumber - 1]->m_pCard;
    }
    else {
        cardType == "monster card"
                ? targetCard = GameExternVars::pOtherPlayer->field.monsterZone.m_monsterZone[zoneNumber - 1]->m_pCard
                : targetCard = GameExternVars::pOtherPlayer->field.spellTrapZone.m_spellTrapZone[zoneNumber - 1]->m_pCard;
    }

    EffectActivator effectActivator(*targetCard);
    connect(&effectActivator, &EffectActivator::lifePointsChanged, this, &Game::onLifePointsChange);
    connect(&effectActivator, &EffectActivator::gameEnded, this, &Game::onGameEnd);
    whichPlayerActivatedEffect == QString::fromStdString("CURRENT_PLAYER")
            ? effectActivator.activateEffect(targetCard->getCardName(), true)
            : effectActivator.activateEffect(targetCard->getCardName(), false);


    if(m_clientID == GameExternVars::currentTurnClientID)
    {
        QPixmap cardBackPixmap(":/resources/pictures/card_back.jpg");
        for(Card *card : GameExternVars::pOtherPlayer->m_hand.getHand()) {
            cardBackPixmap = cardBackPixmap.scaled(QSize(card->width, card->height), Qt::KeepAspectRatio);
            card->setPixmap(cardBackPixmap);
        }
    }
    else
    {
        QPixmap cardBackPixmap(":/resources/pictures/card_back.jpg");
        for(Card *card : GameExternVars::pCurrentPlayer->m_hand.getHand()) {
            cardBackPixmap = cardBackPixmap.scaled(QSize(card->width, card->height), Qt::KeepAspectRatio);
            card->setPixmap(cardBackPixmap);
        }
    }





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

 void Game::deserializeFlip(QDataStream &deserializationStream)
{
    QString cardName;
    QString whichPlayerFlipped;
    qint32 zoneNumber;
    deserializationStream >> whichPlayerFlipped
                          >> cardName
                          >> zoneNumber;

    Card* targetCard;
    whichPlayerFlipped == QString::fromStdString("CURRENT_PLAYER")
            ? targetCard = GameExternVars::pCurrentPlayer->field.monsterZone.m_monsterZone[zoneNumber - 1]->m_pCard
            : targetCard = GameExternVars::pOtherPlayer->field.monsterZone.m_monsterZone[zoneNumber - 1]->m_pCard;

    // We know that its a monster
    MonsterCard *targetMonster = static_cast<MonsterCard *>(targetCard);

    // Change its position
    targetMonster->setPosition(MonsterPosition::ATTACK);
    visuallyFlipMonster(targetMonster, 180);

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

    // If the card was set, we need to make it be face up (so it won't be face-down in the graveyard)
    if(cardType == QString::fromStdString("monster card"))
    {
        MonsterCard *pMonsterCard = static_cast<MonsterCard *>(pDestroyedCard);
        MonsterPosition position = pMonsterCard->getPosition();
        if(position == MonsterPosition::FACE_UP_DEFENSE || position == MonsterPosition::ATTACK)
            visuallyFlipMonster(pMonsterCard, 0);
    }
    else if(cardType == QString::fromStdString("spell card"))
    {
        SpellCard *pSpellCard = static_cast<SpellCard *>(pDestroyedCard);
        SpellTrapPosition position = pSpellCard->getSpellPosition();
        if(position == SpellTrapPosition::SET)
            visuallyFlipSpell(pSpellCard);
    }
    else
    {
        TrapCard *pTrapCard = static_cast<TrapCard *>(pDestroyedCard);
        SpellTrapPosition position = pTrapCard->getTrapPosition();
        if(position == SpellTrapPosition::SET)
            visuallyFlipTrap(pTrapCard);
    }

    // Actually destroy it
    pPlayerWhoOwnedTheDestroyedCard->sendToGraveyard(*pDestroyedCard, pZoneOfTheDestroyedCard); // TODO: Change all other occurences and add zone parameter

    notifyServerThatDeserializationHasFinished();
}

void Game::deserializeGameEnd(QDataStream &deserializationStream)
{
    QString loserName;
    deserializationStream >> loserName;

    // If loserName is our name, it means we lost
    m_clientName == loserName
            ? QMessageBox::information(this, tr("GAME END"), tr("DEFEAT"))
            : QMessageBox::information(this, tr("GAME END"), tr("VICTORY"));

    notifyServerThatDeserializationHasFinished();

    // Close this window
    this->close();
}

void Game::onGameStart(qint32 firstToPlay, qint32 clientID)
{
    std::cout << "Game has started!" << std::endl;

    std::cout << "First one to play is client with id " << firstToPlay << std::endl;
    //std::cout<<ui->labelCurrentPlayerNameDynamic->text().toStdString()<<std::endl;
    ui->enemyPoints->setValue(8000);
    ui->progressBar->setValue(8000);
    ui->progressBar->show();
    ui->enemyPoints->show();
    ui->avatarPlayer->show();
    ui->enemyAvatar->show();
    ui->enemyName->show();
    ui->namePlayer->show();


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

    // We also want to always know our name
    clientID == firstToPlay
            ? m_clientName = QString::fromStdString(GameExternVars::pCurrentPlayer->getPlayerName())
            : m_clientName = QString::fromStdString(GameExternVars::pOtherPlayer->getPlayerName());

    // Set the currentTurnClientID extern var
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
    GameExternVars::pCurrentPlayer->m_hand.setHandCoordinates(m_viewAndSceneWidth, m_windowHeight, flagBottomField);
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
    GameExternVars::pOtherPlayer->m_hand.setHandCoordinates(m_viewAndSceneWidth, m_windowHeight, flagUpperField);
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

    for(Zone* zone : GameExternVars::pCurrentPlayer->field.monsterZone.m_monsterZone) {
        if(!zone->isEmpty()) {
            MonsterCard* monster = static_cast<MonsterCard*>(zone->m_pCard);
            monster->setAlreadyAttackedThisTurn(false);
            monster->setIsRepositionThisTurn(false);
            monster->setIsSummonedThisTurn(false);
        }
    }
    MonsterCard::globalSummonedThisTurn = false;

    for(Zone* zone : GameExternVars::pCurrentPlayer->field.spellTrapZone.m_spellTrapZone) {
        if(!zone->isEmpty() && zone->m_pCard->getCardType() == CardType::TRAP_CARD) {
            zone->m_pCard->setIsSetThisTurn(false);
            zone->m_pCard->setPlayerThatSetThisCard(2);
        }
    }

    for(Zone* zone : GameExternVars::pOtherPlayer->field.spellTrapZone.m_spellTrapZone) {
        if(!zone->isEmpty() && zone->m_pCard->getCardType() == CardType::TRAP_CARD) {
            zone->m_pCard->setPlayerThatSetThisCard(1);
        }
    }
    // Set the label text to indicate that we are in the End Phase:
    emit gamePhaseChanged(GamePhaseExternVars::currentGamePhase);

    // Something may happen here, like checking the effects that resolve in the end phase


    //... (something may happen here eventually)
    emit returnCardToOpponent();
    // TODO: More work is needed here...
    std::cout << "Turn " << m_currentTurn << " ends." << std::endl << std::endl;
    m_currentTurn++;
    emit turnEnded();
    // ui->progressBar->setValue(m_player1.getPlayerLifePoints() - 100);
    // ayerLifePoints(m_player1.getPlayerLifePoints() - 100);

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
        this->ui->btnMainPhase2->setEnabled(false);
        this->ui->btnEndPhase->setEnabled(false);
    }

    // The draw phase begins (this is not optional).
    // There is no need for blockingLoop here since its in onGamePhaseChange()
    GamePhaseExternVars::currentGamePhase = GamePhases::DRAW_PHASE;
    emit gamePhaseChanged(GamePhaseExternVars::currentGamePhase);

    // The current player draws a card (this is not optional).
    GameExternVars::pCurrentPlayer->drawCards(1);

    // Hide the card that we have drawn just now for the other player
    Card* cardThatWeGotJustNow = GameExternVars::pCurrentPlayer->m_hand.getHand().back();

    if(m_clientID != GameExternVars::currentTurnClientID)
    {
        QPixmap cardBackPixmap(":/resources/pictures/card_back.jpg");
        cardBackPixmap = cardBackPixmap.scaled(QSize(cardThatWeGotJustNow->width, cardThatWeGotJustNow->height), Qt::KeepAspectRatio);
        cardThatWeGotJustNow->setPixmap(cardBackPixmap);
    }

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

        std::cout<<"Final avatar is ";
        switch(finalAvatar)
        {
            case(avatars::YUGI):{
                QPixmap avatar(":/resources/pictures/yugi.png");

                std::cout<<" YUGI"<<std::endl;
                ui->avatarPlayer->setStyleSheet("border: 1px solid grey");
                ui->avatarPlayer->setPixmap(avatar);
                ui->avatarPlayer->setScaledContents(true);
                ui->avatarPlayer->setMaximumHeight(200);
                ui->avatarPlayer->setMaximumWidth(200);
                ui->avatarPlayer->setAlignment(Qt::AlignCenter);
                ui->namePlayer->setText(QString::fromStdString(this->m_player1.getPlayerName()));
                break;
            }
            case (avatars::KAIBA):{
                QPixmap avatar(":/resources/pictures/kaiba.png");

                std::cout<<" KAIBA"<<std::endl;
                ui->avatarPlayer->setStyleSheet("border: 1px solid grey");
                ui->avatarPlayer->setPixmap(avatar);
                ui->avatarPlayer->setScaledContents(true);
                ui->avatarPlayer->setMaximumHeight(200);
                ui->avatarPlayer->setMaximumWidth(200);
                ui->avatarPlayer->setAlignment(Qt::AlignCenter);
                ui->namePlayer->setText(QString::fromStdString(this->m_player1.getPlayerName()));


                break;
            }
        }
//        ui->avatarPlayer->setBaseSize(200, 250);
        ui->progressBar->setMaximum(this->m_player1.getPlayerLifePoints());
        ui->progressBar->setMinimum(0);
//        ui->progressBar->setValue(this->m_player1.getPlayerLifePoints());
        ui->progressBar->setFormat("%v");
        ui->progressBar->setRange(0, 8000);


        ui->enemyName->setText(QString::fromStdString(this->m_player2.getPlayerName()));
        ui->enemyPoints->setMaximum(this->m_player2.getPlayerLifePoints());
        ui->enemyPoints->setMinimum(0);
        ui->enemyPoints->setRange(0, 8000);
        ui->enemyPoints->setFormat("%v");
//        ui->enemyPoints->setValue(this->m_player2.getPlayerLifePoints());

        QPixmap avatar(":/resources/pictures/kaiba.png");

//        std::cout<<" KAIBA"<<std::endl;
        ui->enemyAvatar->setStyleSheet("border: 1px solid grey");
        ui->enemyAvatar->setPixmap(avatar);
        ui->enemyAvatar->setScaledContents(true);
        ui->enemyAvatar->setMaximumHeight(200);
        ui->enemyAvatar->setMaximumWidth(200);
        ui->enemyAvatar->setAlignment(Qt::AlignCenter);
    }
}

void Game::onCardHoverEnter(Card &card)
{
    std::cout << "Card " << card.getCardName() << " hover-entered!" << std::endl;

    QString cardPosition;

    /* If the card is a monster, we want its ATK/DEF in card description too.
     * If its not a monster, it will be empty string and won't mess with the description. */
    std::string atkDefIfMonster = "";
    if(card.getCardType() == CardType::MONSTER_CARD)
    {
        MonsterCard *pMonsterCard = static_cast<MonsterCard *>(&card);
        atkDefIfMonster += "ATK: " + std::to_string(pMonsterCard->getAttackPoints()) + "  /  DEF: " + std::to_string(pMonsterCard->getDefensePoints());

        cardPosition = MonsterCard::monsterPositionEnumToQString.at(pMonsterCard->getPosition());
    }
    else if(card.getCardType() == CardType::SPELL_CARD)
    {
        SpellCard *pSpellCard = static_cast<SpellCard *>(&card);

        cardPosition = SpellCard::spellTrapPositionEnumToQString.at(pSpellCard->getSpellPosition());
    }
    else
    {
        TrapCard *pTrapCard = static_cast<TrapCard *>(&card);

        cardPosition = TrapCard::spellTrapPositionEnumToQString.at(pTrapCard->getTrapPosition());
    }

    // Set the correct card image
    QPixmap pix;
    pix.load(QString::fromStdString(card.imagePath));
    pix = pix.scaled(ui->labelImage->size(), Qt::KeepAspectRatio);
    ui->labelImage->setPixmap(pix);

    // Set the description text
    ui->textBrowserEffect->setText(QString::fromStdString(card.getCardDescription() + "\n\n\n" + atkDefIfMonster));

    // Enable card info ui only if we hover our cards and not opponent's
    // Our cards are always at the bottom half of the scene
    if(card.y() >= m_windowHeight / 2 || (card.y() < m_windowHeight / 2 && cardPosition != "FACE_DOWN_DEFENSE" && cardPosition != "SET"))
    {
        ui->labelImage->setVisible(true);
        ui->textBrowserEffect->setVisible(true);
    }
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

    // We only want current client to be able to see card menus, and only on his own cards
    if(m_clientID == GameExternVars::currentTurnClientID && card->y() >= m_windowHeight / 2)
        card->cardMenu->isVisible() == false ? card->cardMenu->show() : card->cardMenu->hide();
}

void Game::onActivateFromHand(Card &activatedCard) {
    //its only spell card for now that can be activated from hand
    activatedCard.setIsActivated(true);
    SpellCard* activatedSpellCard = static_cast<SpellCard*>(&activatedCard);
    activatedSpellCard->setPosition(SpellTrapPosition::FACE_UP);
    GameExternVars::pCardToBePlacedOnField = activatedSpellCard;

    if(activatedSpellCard->getSpellType() == SpellType::FIELD_SPELL)
    {
        activatedSpellCard->setZValue(1);
        GameExternVars::pCurrentPlayer->field.fieldZone->putInZone(activatedSpellCard);
    }
    else
        GameExternVars::pCurrentPlayer->field.spellTrapZone.colorFreeZones();


}

// Slots for card menu UI
void Game::onActivateButtonClick(Card &card)
{
    std::cout << "Activate button clicked on card " << card.getCardName() << std::endl;

    // Idea: Map of function pointers for effects
    const std::string cardName = card.getCardName();
    if(card.getCardLocation() == CardLocation::HAND) {
        GameExternVars::pCurrentPlayer->m_hand.removeFromHand(card);
        emit activateFromHand(card);
    }
    else {

        // Effect activator is needed for effect handling
        EffectActivator effectActivator(card);
        // We connect every signal from EffectActivator to our slots in Game:
        connect(&effectActivator, &EffectActivator::lifePointsChanged, this, &Game::onLifePointsChange);
        connect(&effectActivator, &EffectActivator::gameEnded, this, &Game::onGameEnd);
        effectActivator.activateEffect(cardName, true);

        if(m_clientID == GameExternVars::currentTurnClientID)
        {
            QPixmap cardBackPixmap(":/resources/pictures/card_back.jpg");
            for(Card *card : GameExternVars::pOtherPlayer->m_hand.getHand()) {
                cardBackPixmap = cardBackPixmap.scaled(QSize(card->width, card->height), Qt::KeepAspectRatio);
                card->setPixmap(cardBackPixmap);
            }
        }
        else
        {
            QPixmap cardBackPixmap(":/resources/pictures/card_back.jpg");
            for(Card *card : GameExternVars::pCurrentPlayer->m_hand.getHand()) {
                cardBackPixmap = cardBackPixmap.scaled(QSize(card->width, card->height), Qt::KeepAspectRatio);
                card->setPixmap(cardBackPixmap);
            }
        }



        qint32 zoneNumber = findZoneNumber(card, GameExternVars::pCurrentPlayer);
        // Notify the server / other client
        QEventLoop blockingLoop;
        connect(this, &Game::deserializationFinished, &blockingLoop, &QEventLoop::quit);
        QByteArray buffer;
        QDataStream outDataStream(&buffer, QIODevice::WriteOnly);
        outDataStream.setVersion(QDataStream::Qt_5_15);
        outDataStream << QString::fromStdString("EFFECT_ACTIVATED")
                      << QString::fromStdString("CURRENT_PLAYER")
                      << QString::fromStdString(cardName) // Who activated the effect
                      << QString::fromStdString(card.getCardTypeString())
                      << zoneNumber;

        sendDataToServer(buffer);
        blockingLoop.exec();

        connect(&effectActivator, &EffectActivator::effectMonsterReborn, this, &Game::onMonsterReborn);
        connect(&effectActivator, &EffectActivator::effectChangeOfHeart, this, &Game::onChangeOfHeart);
        
        if(card.shouldBeSentToGraveyard()) {//this needs to be implemented
            delay();
            card.getPlayerThatSetThisCard() == 1
                    ? GameExternVars::pCurrentPlayer->sendToGraveyard(card)
                    : GameExternVars::pOtherPlayer->sendToGraveyard(card);

            QEventLoop blockingLoop2;
            connect(this, &Game::deserializationFinished, &blockingLoop2, &QEventLoop::quit);
            QByteArray buffer2;
            QDataStream outDataStream2(&buffer2, QIODevice::WriteOnly);
            outDataStream2.setVersion(QDataStream::Qt_5_15);
            outDataStream2 << QString::fromStdString("DESTROY_CARD") // Notify the server that a card was destroyed
                           << QString::fromStdString("CURRENT_PLAYER") // Who owns a card that was destroyed
                           << QString::fromStdString(card.getCardTypeString())
                           << zoneNumber; // Where is the monster card located

            sendDataToServer(buffer2);
            blockingLoop2.exec();
        }
        //if(shouldBeSentToGraveyard) this needs to be implemented
    }
}
void Game::onChangeOfHeart(Player &current, Player &opponent) {
    for (Zone *zone : opponent.field.monsterZone.m_monsterZone)
    {
        if (!zone->isEmpty() && zone->m_pCard->getCardType() == CardType::MONSTER_CARD)
        {
            opponent.field.graveyard->sendToGraveyard(*(zone->m_pCard));
//            opponent.field.monsterZone.removeFromMonsterZone(zone);
            bool flag = false;
            for (Zone *zone1 : current.field.monsterZone.m_monsterZone){
                if (zone1->isEmpty() && flag == false)
                {
                    current.field.monsterZone.placeInMonsterZone(zone->m_pCard, zone1);
                    flag = true;
                    GameExternVars::pCardToBeReturned = zone->m_pCard;
                    zone->m_pCard = nullptr;
                    return;
                }
            }
        }
    }

}
void Game::onMonsterReborn(Player &p)
{
//    std::cout<<"POCETAK MONSTER REBORN KARTE "<<std::endl;
    for (Card *c : p.field.graveyard->getGraveyard())
    {
        if (c->getCardType() == CardType::MONSTER_CARD)
        {
//            p.field.graveyard->removeFromGraveyard(*c);
            for (Zone *zone : p.field.monsterZone.m_monsterZone)
            {
                if (zone->isEmpty())
                {
                    p.field.graveyard->removeFromGraveyard(*c);
                    p.field.monsterZone.placeInMonsterZone(c, zone);
                    return;
                }
            }
        }
    }
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
    monsterCard->setIsSummonedThisTurn(true);
    MonsterCard::globalSummonedThisTurn = true;

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


    attackingMonster.cardMenu->setVisible(false);
}

void Game::onRepositionButtonClick(Card &card)
{
    std::cout << "Reposition button clicked for card " << card.getCardName() << std::endl;

    // We are sure that this card is a MonsterCard since only monsters can change their position to defense or attack
    MonsterCard *monsterCard = static_cast<MonsterCard *>(&card);

    // Change the position
    monsterCard->changePosition();
    monsterCard->setIsRepositionThisTurn(true);
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

    card.cardMenu->setVisible(false);
}

void Game::onFlipButtonClick(Card &card)
{
    MonsterCard *monsterCard = static_cast<MonsterCard *>(&card);
    visuallyFlipMonster(monsterCard, 0);
    monsterCard->setPosition(MonsterPosition::ATTACK);
    monsterCard->setIsRepositionThisTurn(true);

    qint32 zoneNumber = findZoneNumber(*monsterCard, GameExternVars::pCurrentPlayer);

    // Notify the server / other client
    QEventLoop blockingLoop;
    connect(this, &Game::deserializationFinished, &blockingLoop, &QEventLoop::quit);
    QByteArray buffer;
    QDataStream outDataStream(&buffer, QIODevice::WriteOnly);
    outDataStream.setVersion(QDataStream::Qt_5_15);
    outDataStream << QString::fromStdString("FLIP")
                  << QString::fromStdString("CURRENT_PLAYER")
                  << QString::fromStdString(monsterCard->getCardName()) // TODO: This is maybe unneeded, since we can locate the monster by just using the zone number
                  << zoneNumber; // Zone number, so we can locate the monster
    sendDataToServer(buffer);
    blockingLoop.exec();

    EffectRequirement effectRequirement(*monsterCard);
    bool cardActivationRequirement = effectRequirement.isActivatable(monsterCard->getCardName());
    if(cardActivationRequirement) {
        delay();
        onActivateButtonClick(*monsterCard);
    }


    card.cardMenu->setVisible(false);
}


/* TODO: This should accept the targetPlayer as an argument, because otherwise we always print currentPlayer's hp,
         even if it was other player's health that had changed. */
void Game::onLifePointsChange(Player &targetPlayer) // const?
{
    std::cout << "Current health points for player " << targetPlayer.getPlayerName() << " : "<< targetPlayer.getPlayerLifePoints() << std::endl;

    // Update labels
    ui->labelCurrentPlayerLpDynamic->setText(QString::fromStdString(std::to_string(GameExternVars::pCurrentPlayer->getPlayerLifePoints())));
    ui->labelOtherPlayerLpDynamic->setText(QString::fromStdString(std::to_string(GameExternVars::pOtherPlayer->getPlayerLifePoints())));
    ui->progressBar->setValue(GameExternVars::pCurrentPlayer->getPlayerLifePoints());
    ui->enemyPoints->setValue(GameExternVars::pOtherPlayer->getPlayerLifePoints());


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


    // Display a pop-up window for both players that the game has ended and tell them the result.
    QString loserName = QString::fromStdString(loser.getPlayerName());
    m_clientName == loserName
            ? QMessageBox::information(this, tr("GAME END"), tr("DEFEAT"))
            : QMessageBox::information(this, tr("GAME END"), tr("VICTORY"));

    QEventLoop blockingLoop2;
    connect(this, &Game::deserializationFinished, &blockingLoop2, &QEventLoop::quit);
    QByteArray buffer2;
    QDataStream outDataStream2(&buffer2, QIODevice::WriteOnly);
    outDataStream2.setVersion(QDataStream::Qt_5_15);
    outDataStream2 << QString::fromStdString("GAME_END")
                   << loserName;
    sendDataToServer(buffer2);
    blockingLoop2.exec();


    // Close this window
    this->close();
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
        monsterCard->setIsSummonedThisTurn(true);
        MonsterCard::globalSummonedThisTurn = true;

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
        pMonsterCard->setIsSummonedThisTurn(true);
    }
    else if(card->getCardType() == CardType::SPELL_CARD || card->getCardType() == CardType::TRAP_CARD) {
        GameExternVars::pCurrentPlayer->field.spellTrapZone.placeInSpellTrapZone(card, clickedRedZone);
        card->setCardLocation(CardLocation::FIELD);
        card->setIsSetThisTurn(true);
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

    if(card->getIsActivated()) {
        card->cardMenu->activateButton->click();
    }

    card->cardMenu->setVisible(false);
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

void Game::onBlueZoneClick(Zone *clickedBlueZone) {


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

void Game::onConnectButtonClick()
{
    ui->btnConnect->setEnabled(false);

    // Parse the address and the port
    QString addr = ui->textEditAddress->toPlainText().trimmed();
    int port = ui->textEditPort->toPlainText().trimmed().toInt();

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

void Game::onCardAddedToScene(Card *card)
{
    //Needed to show a card
    connect(card, &Card::cardSelected, this, &Game::onCardSelect);
    connect(card, &Card::cardHoveredEnter, this, &Game::onCardHoverEnter);
    connect(card, &Card::cardHoveredLeave, this, &Game::onCardHoverLeave);
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
    connect(card->cardMenu->flipButton, &QPushButton::clicked, this, [this, card](){
        onFlipButtonClick(*card);
    });
    ui->graphicsView->scene()->addItem(card);
    ui->graphicsView->scene()->addWidget(card->cardMenu);
    card->cardMenu->setVisible(false);
    // By default we don't want to show card info unless the card is hovered
    ui->labelImage->setVisible(false);
    ui->textBrowserEffect->setVisible(false);
}


void Game::onReturnCardToOpponent(){

    if(GameExternVars::pCardToBeReturned == nullptr)
        return;
    for (Zone *zone : GameExternVars::pCurrentPlayer->field.monsterZone.m_monsterZone)
    {
        if (zone->m_pCard == GameExternVars::pCardToBePlacedOnField)
        {
            GameExternVars::pCurrentPlayer->field.monsterZone.removeFromMonsterZone(zone);
            break;
        }
    }
    for (Zone *zone : GameExternVars::pOtherPlayer->field.monsterZone.m_monsterZone)
    {
        if (zone->isEmpty())
        {
            GameExternVars::pOtherPlayer->field.graveyard->removeFromGraveyard(*GameExternVars::pCardToBeReturned);
            GameExternVars::pOtherPlayer->field.monsterZone.placeInMonsterZone(GameExternVars::pCardToBeReturned, zone);
            GameExternVars::pCardToBeReturned = nullptr;
            return;
        }
    }
}



