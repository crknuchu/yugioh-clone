#include "headers/Game.h"
#include "headers/ui_mainwindow.h" // TODO: Rename this file to avoid confusion
#include "headers/Monstercard.h"

#include <iostream>
#include <random>
#include <map>

#include <QGraphicsScene>
#include <QGraphicsLayout>



// Global variables:
// TODO: Global or not
const std::map<GamePhases, QString> gamePhaseToQString{
    {GamePhases::DRAW_PHASE,        "DRAW PHASE"},
    {GamePhases::STANDBY_PHASE,     "STANDBY PHASE"},
    {GamePhases::MAIN_PHASE1,       "MAIN PHASE 1"},
    {GamePhases::BATTLE_PHASE,      "BATTLE PHASE"},
    {GamePhases::MAIN_PHASE2,       "MAIN PHASE 2"},
    {GamePhases::END_PHASE,         "END PHASE"}
};


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

  // The first one gets 6 cards:
  m_pCurrentPlayer->drawCards(6);

  // The other one gets 5 cards
  // Without m_pOtherPlayer:  *m_pCurrentPlayer == m_player1 ? m_player2.drawCards(5) : m_player1.drawCards(5);
  // With m_pOtherPlayer:
  m_pOtherPlayer->drawCards(5);
}

void Game::playFirstTurn() {
    m_currentTurn = 1;
    std::cout << "Current turn: " << m_currentTurn << std::endl;

    m_currentGamePhase = GamePhases::DRAW_PHASE;
    emit gamePhaseChanged(m_currentGamePhase);

    firstTurnSetup();

    m_currentGamePhase = GamePhases::STANDBY_PHASE;
    emit gamePhaseChanged(m_currentGamePhase);
    // ...

    m_currentGamePhase = GamePhases::MAIN_PHASE1;
    emit gamePhaseChanged(m_currentGamePhase);

    /*
     *  Placeholder for the first turn's loop.
     *  Since the player action mechanisms are still not implemented (TODO),
     *  for now we only have a while loop that instantly finishes.
     */
    while(m_currentGamePhase != GamePhases::END_PHASE)
    {
      /*
       *  Here the firstPlayer will play his MainPhase1 in the first turn.
       *  For now, we still don't have playMP1() implemented.
       */

       m_currentGamePhase = GamePhases::END_PHASE;
       emit gamePhaseChanged(m_currentGamePhase);
    }
    std::cout << "Turn " << m_currentTurn << " ends." << std::endl << std::endl;
}

void Game::playTurn() {
    std::cout << "Current turn: " << m_currentTurn << std::endl;
    // The player switch:
    switchPlayers();
    std::cout << "Current player: " << m_pCurrentPlayer->getPlayerName() << std::endl;

    // Draw Phase begins:
    m_currentGamePhase = GamePhases::DRAW_PHASE;
    emit gamePhaseChanged(m_currentGamePhase);

    // The current player draws a card (this is not optional).
    m_pCurrentPlayer->drawCards(1);


    // The draw phase ends and the standby phase begins (this is not optional).
    m_currentGamePhase = GamePhases::STANDBY_PHASE;
    emit gamePhaseChanged(m_currentGamePhase);
    // ...

    // The standby phase ends and the main phase 1 begins (this is not optional).
    m_currentGamePhase = GamePhases::MAIN_PHASE1;
    emit gamePhaseChanged(m_currentGamePhase);
    // ...


    // The battle phase is optional.
    // Placeholder pseudo-code for event listening:
    /*
     * if BP button was clicked                     // TODO
     * then m_currentGamePhase = GamePhases::BATTLE_PHASE;
     * ...
    */


    /* We (optionally) enter the MP2 only if there was a battle phase
     * and the MP2 button was clicked (TODO) */
    if (m_currentGamePhase == GamePhases::BATTLE_PHASE)
    {
        m_currentGamePhase = GamePhases::MAIN_PHASE2;
        // ...
    }

    // The end phase begins if the EP button was clicked (TODO):
    m_currentGamePhase = GamePhases::END_PHASE;
    // ...


    std::cout << "Turn " << m_currentTurn << " ends." << std::endl << std::endl;
    m_currentTurn++;
}

void Game::start() {

  std::cout << "The game has started." << std::endl;

  int tmpBlockLoop; // Needed for now for the cin at the end of our while loop, will be removed when checkLifePoints is implemented.

  /*
   *  First turn is special (there is no battle phase and main phase 2),
   *  so it has its own function:
   */
  playFirstTurn();
  m_currentTurn++;

  // Other turns are all the same structure-wise practically:
  while (true)
  {
    playTurn();

    /*
     *  For now, the game runs as an infinite loop (the cin is added as a blocking operation).
     *  checkLifePoints function will be implemented as the way to end the game.
     */
    std::cin >> tmpBlockLoop;
  }
  std::cout << "The game has ended." << std::endl;
}



// QT related stuff:
void Game::setupConnections() {
    // Game
    connect(this, &Game::mainWindowResized, this, &Game::onMainWindowResize);
    connect(this, &Game::gamePhaseChanged, this, &Game::onGamePhaseChange);

    // Buttons
    connect(ui->btnBattlePhase, &QPushButton::clicked, this, &Game::btnBattlePhaseClicked);
    connect(ui->btnMainPhase2, &QPushButton::clicked, this, &Game::btnMainPhase2Clicked);
    connect(ui->btnEndPhase, &QPushButton::clicked, this, &Game::btnEndPhaseClicked);

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
void Game::btnBattlePhaseClicked()
{
    std::cout << "Battle phase button clicked" << std::endl;
    m_currentGamePhase = GamePhases::BATTLE_PHASE;

    emit gamePhaseChanged(m_currentGamePhase);
}

void Game::btnMainPhase2Clicked()
{
    std::cout << "Main phase 2 button clicked" << std::endl;
    m_currentGamePhase = GamePhases::MAIN_PHASE2;

    emit gamePhaseChanged(m_currentGamePhase);
}

void Game::btnEndPhaseClicked()
{
    std::cout << "End phase button clicked" << std::endl;
    m_currentGamePhase = GamePhases::END_PHASE;

    // Set the label text to indicate that we are in the End Phase:
    emit gamePhaseChanged(m_currentGamePhase);

    /*
     *  FIXME: This breaks the program, probably because we didn't call firstTurnSetup() yet,
     *  so m_pCurrentPlayer and m_pOtherPlayer have undefined values and can't be switched, leading to a SEGFAULT.
     */
    // In the end phase, we switch the players:
    //    switchPlayers();
}

void Game::onGamePhaseChange(const GamePhases &newGamePhase)
{
    // When game phase changes, we update label's text.
    // We use at() instead of [] because [] is not const and our map is.
    ui->labelGamePhase->setText(gamePhaseToQString.at(newGamePhase));
}





void Game::onMainWindowResize(QResizeEvent *resizeEvent)
{
    std::cout << "Window has been resized!" << std::endl;

    // Set our private variables to the new window size:
    m_windowWidth = resizeEvent->size().width();
    m_windowHeight = resizeEvent->size().height();

    // Check: Very rarely, this displays the same width/height as the old window?
    std::cout << "New main window width/height: " << m_windowWidth << " / " << m_windowHeight << std::endl;

    ui->graphicsView->setWindowTitle("Yu-Gi-Oh!");
    ui->graphicsView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->graphicsView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    /* TODO:
     *  This makes the scene display correctly next to the buttons,
     *  but its probably only because qt is smart enough to figure out
     *  that we don't want our scene to be rendered over our buttons.
     *
     *  Also, after doing this setFixedSize, scene()->width() will be shown as m_windowWidth,
     *  even though graphically that isn't really true (because of the vertical layout for buttons)
     */
    ui->graphicsView->setFixedSize(m_windowWidth, m_windowHeight);
    ui->graphicsView->scene()->setSceneRect(0, 0, m_windowWidth, m_windowHeight);

    // TODO: Check if this is needed
    ui->graphicsView->fitInView(0, 0, m_windowWidth, m_windowHeight, Qt::KeepAspectRatio);


    std::cout << "Scene width: " << ui->graphicsView->scene()->width();


    // FIXME: Memory leak.
    // This is a placeholder, in future we won't initialize cards here probably.
    MonsterCard* monsterCard1 = new MonsterCard(3000, 2500, MonsterType::DRAGON,
                                                MonsterKind::NORMAL_MONSTER, MonsterAttribute::LIGHT,
                                                8, "Sibirski Plavac", CardType::MONSTER_CARD,
                                                CardLocation::HAND, "Opis"
                                                );

    MonsterCard* monsterCard2 = new MonsterCard(3000, 2500, MonsterType::DRAGON,
                                                MonsterKind::NORMAL_MONSTER, MonsterAttribute::LIGHT,
                                                8, "Sibirski Plavac", CardType::MONSTER_CARD,
                                                CardLocation::HAND, "Opis"
                                                );

    monsterCard1->setName("monsterCard1");
    monsterCard2->setName("monsterCard2");



//    monsterCard2->setFixedWidth(500);

    monsterCard1->setPos(450, 450);

    ui->graphicsView->scene()->addItem(monsterCard1);



    // WIP: Image label
    // TODO: Move this to onHover slot
    ui->imageLabel->setAlignment(Qt::AlignCenter);


    QPixmap pix;
    pix.load(":/resources/blue_eyes.jpg");
    pix = pix.scaled(ui->imageLabel->size(), Qt::KeepAspectRatio);
    ui->imageLabel->setPixmap(pix);




    // WIP: Background image
    // TODO: Find another image of the field
    QPixmap background(":/resources/field2.png");
    background = background.scaled(this->size().width(), this->size().height() / 2, Qt::IgnoreAspectRatio);
    QBrush brush(QPalette::Window, background);
    ui->graphicsView->setBackgroundBrush(brush);
}





