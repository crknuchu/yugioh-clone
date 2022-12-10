#include "headers/ui_mainwindow.h" // TODO: Rename this file to avoid confusion
#include "headers/Game.h"
#include "headers/Monstercard.h"
#include "headers/EffectActivator.h"

#include <iostream>
#include <random>
#include <map>
#include <functional>

#include <QGraphicsScene>
#include <QGraphicsLayout>



// Class definitions:
Game::Game(Player p1, Player p2, QWidget *parent)
    : QMainWindow(parent),
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



    // First turn setup at the beginning of the game:
    firstTurnSetup();
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
    Player tmp = *m_pCurrentPlayer;
    *m_pCurrentPlayer = *m_pOtherPlayer;
    *m_pOtherPlayer = tmp;

    std::cout << "Current player is: " << *m_pCurrentPlayer << std::endl;
}

void Game::firstTurnSetup() {
  // The game decides who will play first:
  if (decideWhoPlaysFirst() == 1)
  {
      m_pCurrentPlayer = &m_player1;
      m_pOtherPlayer = &m_player2;
  }
  else
  {
      m_pCurrentPlayer = &m_player2;
      m_pOtherPlayer = &m_player1;
  }

  std::cout << "The first one to play is " << m_pCurrentPlayer->getPlayerName() << std::endl;

  m_currentTurn = 1;
  GamePhase::currentGamePhase = GamePhasesEnum::DRAW_PHASE;
  emit gamePhaseChanged(GamePhase::currentGamePhase);

  // The first one gets 6 cards:
  m_pCurrentPlayer->drawCards(6);

  // The other one gets 5 cards
  // Without m_pOtherPlayer:  *m_pCurrentPlayer == m_player1 ? m_player2.drawCards(5) : m_player1.drawCards(5);
  // With m_pOtherPlayer:
  m_pOtherPlayer->drawCards(5);
}


// QT related stuff:
void Game::setupConnections() {
    // Game
    connect(this, &Game::mainWindowResized, this, &Game::onMainWindowResize);
    connect(this, &Game::gamePhaseChanged, this, &Game::onGamePhaseChange);
    connect(this, &Game::turnEnded, this, &Game::onTurnEnd);

    // WIP
    connect(this, &Game::cardAddedToScene, this, &Game::onCardAddedToScene);

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
    GamePhase::currentGamePhase = GamePhasesEnum::BATTLE_PHASE;

    emit gamePhaseChanged(GamePhase::currentGamePhase);

    /* We enable Main Phase 2 button only if the BP button was clicked
     * since there can't be MP2 if there was no BP previously */
    ui->btnMainPhase2->setEnabled(true);
}

void Game::onMainPhase2ButtonClick()
{
    std::cout << "Main phase 2 button clicked" << std::endl;
    GamePhase::currentGamePhase = GamePhasesEnum::MAIN_PHASE2;

    emit gamePhaseChanged(GamePhase::currentGamePhase);
}

void Game::onEndPhaseButtonClick()
{
    std::cout << "End phase button clicked" << std::endl;
    GamePhase::currentGamePhase = GamePhasesEnum::END_PHASE;

    // Set the label text to indicate that we are in the End Phase:
    emit gamePhaseChanged(GamePhase::currentGamePhase);

    //... (something may happen here eventually)

    // TODO: More work is needed here...
    std::cout << "Turn " << m_currentTurn << " ends." << std::endl << std::endl;
    m_currentTurn++;
    emit turnEnded();

}

void Game::onGamePhaseChange(const GamePhasesEnum &newGamePhase)
{
    // When game phase changes, we update label's text.
    // We use at() instead of [] because [] is not const and our map is.
    ui->labelGamePhase->setText(GamePhase::gamePhaseToQString.at(newGamePhase));
}


/* This is actually a slot that does things at the beginning of a new turn
   so it could be called beginNewTurn or onNewTurn or something like that...*/
void Game::onTurnEnd() {
    // Disable MP2 Button unless BP button was clicked
    ui->btnMainPhase2->setEnabled(false);



    // Switch the players:
    switchPlayers();

    // The draw phase begins (this is not optional).
    GamePhase::currentGamePhase = GamePhasesEnum::DRAW_PHASE;
    emit gamePhaseChanged(GamePhase::currentGamePhase);

    // The current player draws a card (this is not optional).
    m_pCurrentPlayer->drawCards(1);



    // The draw phase ends and the standby phase begins (this is not optional).
    GamePhase::currentGamePhase = GamePhasesEnum::STANDBY_PHASE;
    emit gamePhaseChanged(GamePhase::currentGamePhase);

    /* ... Something may happen here due to effects (maybe we should call checkEffects()
     or something similar that will check if there are effects to be activated in SP */



    // The standby phase ends and the main phase 1 begins (this is not optional).
    GamePhase::currentGamePhase = GamePhasesEnum::MAIN_PHASE1;
    emit gamePhaseChanged(GamePhase::currentGamePhase);

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

    // Set our private variables to the new window size:
    m_windowWidth = resizeEvent->size().width();
    m_windowHeight = resizeEvent->size().height();

    // Check: Very rarely, this displays the same width/height as the old window
//    std::cout << "New main window width/height: " << m_windowWidth << " / " << m_windowHeight << std::endl;


    // FIXME: Memory leak.
    // TODO: Move this elsewhere.
    // MonsterCard::MonsterCard(const std::string &cardName, int attackPoints, int defensePoints,
    // int level, MonsterType type, MonsterKind kind, MonsterAttribute attribute,bool active,Position position,bool alreadyAttack, CardType cardType, CardLocation cardLocation, const std::string &cardDescription,bool summonedThisTurn)
    MonsterCard* monsterCard1 = new MonsterCard("Lord of D", 3000, 2500, 4,
                                                MonsterType::SPELLCASTER, MonsterKind::EFFECT_MONSTER,
                                                MonsterAttribute::DARK, false, Position::ATTACK, false,
                                                CardType::MONSTER_CARD, CardLocation::HAND,
                                                "Neither player can target Dragon monsters on the field with card effects."
                                                );
    monsterCard1->setPos(450, 450);
    ui->graphicsView->scene()->addItem(monsterCard1);

    // Notify the game that a card was added.
    emit cardAddedToScene(monsterCard1);

    // WIP: UI components
    // Game phase buttons and label:
    ui->labelGamePhase->setAlignment(Qt::AlignCenter);

    // Card info:
    ui->labelImage->setAlignment(Qt::AlignCenter);

    // TODO: getEffect()
//    ui->textBrowserEffect->setText(monsterCard1->getEffect());

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
    const int leftVerticalLayoutHeight = ui->leftVerticalLayout->sizeHint().height();
//    qDebug("Layout Width: %d, height: %d", leftVerticalLayoutWidth, leftVerticalLayoutHeight);

    const int viewAndSceneWidth = m_windowWidth - (leftVerticalLayoutWidth);
    ui->graphicsView->setFixedSize(viewAndSceneWidth, m_windowHeight);
    ui->graphicsView->scene()->setSceneRect(0, 0, viewAndSceneWidth, m_windowHeight);

    // TODO: Check if this is needed
    ui->graphicsView->fitInView(0, 0, viewAndSceneWidth, m_windowHeight, Qt::KeepAspectRatio);

//    std::cout << "Scene width: " << ui->graphicsView->scene()->width();

    // WIP: Background image
    // TODO: Find another image of the field
    QPixmap background(":/resources/field2.png");
    background = background.scaled(viewAndSceneWidth,  this->size().height() / 2, Qt::IgnoreAspectRatio);
    QBrush brush(QPalette::Window, background);
    ui->graphicsView->setBackgroundBrush(brush);

    // TODO: Maybe this can be a "starting" point for our program
    /* For example, we could call firstTurnSetup here ...
     * Problem with that is that it would restart the game every time the main window gets resized.
     * Solution ideas:
     *  1) Flags
     *  2) ?
     */

}

// TODO: const Card *&Card
void Game::onCardAddedToScene(const Card *card)
{
    // TODO: If exact subclass of Card is needed here eventually, we could check with:
    /*
     *      1) Dynamic cast
     *      2) Make every card have a field which describes if its a monster, spell or a trap
     *         and then static cast into that class
     *      3) Templates?
     */

    std::cout << "A card was added to the scene!" << std::endl;
    std::cout << "Card name: " << card->getCardName() << std::endl;


    // Pseudo-code
    /* -> Call setCardMenu() that determines the appearance of card menu based on flags
     *  -> calls cardMenu.set() that sets the appropriate fields to false
    */

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

    // FIXME: Problem maybe happens because card is QGraphicsPixmapItem which is not a QOBJECT (even though we used Q_OBJECT macro in Card.h)
//    connect(card, &Card::cardHovered, this, &Game::onCardHover);
}

void Game::onCardHover(Card * card)
{
    std::cout << "Card " << card->getCardName() << " hovered!" << std::endl;
}


// Slots for card menu UI
void Game::onActivateButtonClick(const Card &card)
{
    std::cout << "Activate button clicked on card " << card.getCardName() << std::endl;

    // Idea: Map of function pointers for effects
    const std::string cardName = card.getCardName();

    // Activate card's effect
    EffectActivator effectActivator;

    try {
        auto effectFunctionPointer = effectActivator.effectMap.at(cardName);

        // (effectActivator.*funcPointer)(); // This is the same as the invoke call below.
        // If the first argument is a pointer to member func, invoke expects an object that owns it to be a first argument.
        std::invoke(effectFunctionPointer, effectActivator);
    } catch(std::out_of_range &e) {
        std::cerr << "Error: That card doesn't have an effect! Out of range exception from: " << e.what() << std::endl;
    }
}

void Game::onSummonButtonClick(const Card &card) {
    std::cout<< "Summon button was clicked on card " << card.getCardName() << std::endl;
}


void Game::onSetButtonClick(const Card &card)
{
    std::cout << "Set button clicked on card " << card.getCardName() << std::endl;


}




