#include "headers/Game.h"
#include "headers/ui_mainwindow.h" // TODO: Rename this file to avoid confusion
//#include "headers/Card.h"

#include <iostream>
#include <random>
#include <QGraphicsScene>


// QMainWindow != Ui::MainWindow

Game::Game(Player p1, Player p2, QWidget *parent)
    : QMainWindow(parent),
      ui(new Ui::MainWindow),
      m_player1(p1),
      m_player2(p2)

{
    ui->setupUi(this);

    // Setup connections:
    setupConnections();

    /*
     *  By using ui_mainwindow.h, we hopefully don't need to create the QGraphicsScene ourselves and hardcode it,
     *  since its done automatically in the mainwindow.ui file that is changed through Design tab.
     */


    // TODO: Do this with ui->scene_object_name:

    //    scene = new QGraphicsScene(this);

    //    scene->setSceneRect(0,0,800,600); //make the scene not hardcoded

    //    setScene(scene);

    //    setFixedSize(800,600);
    //    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    //    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    //    setWindowTitle("Yu-Gi-Oh!");


    //creating items
    // Card *c = new Card();
    // c->setName("karta1");
    // Card *c1 = new Card();
    // c1->setName("karta2");

    // //adding items
    // scene->addItem(c);
    // scene->addItem(c1);
    // c->setPos(0, scene->height() - c->getHeight());
}

Game::Game() {}
Game::~Game() {
    delete ui;
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
    firstTurnSetup();

    m_currentGamePhase = GamePhases::STANDBY_PHASE;
    // ...

    m_currentGamePhase = GamePhases::MAIN_PHASE1;

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

    // The current player draws a card (this is not optional).
    m_pCurrentPlayer->drawCards(1);


    // The draw phase ends and the standby phase begins (this is not optional).
    m_currentGamePhase = GamePhases::STANDBY_PHASE;
    // ...

    // The standby phase ends and the main phase 1 begins (this is not optional).
    m_currentGamePhase = GamePhases::MAIN_PHASE1;
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
    connect(ui->btnBattlePhase, &QPushButton::clicked, this, &Game::btnBattlePhaseClicked);
    connect(ui->btnMainPhase2, &QPushButton::clicked, this, &Game::btnMainPhase2Clicked);
    connect(ui->btnEndPhase, &QPushButton::clicked, this, &Game::btnEndPhaseClicked);
}

// Slots:
void Game::btnBattlePhaseClicked()
{
    std::cout << "Battle phase button clicked" << std::endl;
    m_currentGamePhase = GamePhases::BATTLE_PHASE;
//    std::cout << "m_currentGamePhase: " << m_currentGamePhase << std::endl;
}

void Game::btnMainPhase2Clicked()
{
    std::cout << "Main phase 2 button clicked" << std::endl;
    m_currentGamePhase = GamePhases::MAIN_PHASE2;
}

void Game::btnEndPhaseClicked()
{
    std::cout << "End phase button clicked" << std::endl;
    m_currentGamePhase = GamePhases::END_PHASE;
}




