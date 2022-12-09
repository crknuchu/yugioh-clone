#include "headers/Game.h"
#include "headers/ui_mainwindow.h" // TODO: Rename this file to avoid confusion
#include "headers/Monstercard.h"

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
    /*
     *  !! FIXME: For some reason, uic (Qt Ui Compiler) is not run automatically on Build,
     *            so any additions to the .ui file must be compiled manually
     *            by using uic mainwindow.ui -o ui_mainwindow.h
     */

    ui->setupUi(this);

    // Setup connections:
    setupConnections();

    // Create the scene:
    scene = new QGraphicsScene(this);

    ui->graphicsView->setScene(scene);

    ui->graphicsView->setSceneRect(0,0,800,600); // Make the scene not hardcoded

    //    setFixedSize(800,600);
    ui->graphicsView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->graphicsView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->graphicsView->setWindowTitle("Yu-Gi-Oh!"); // This compiles even without ui->graphicsView


    // Creating items
    // TODO: Should monstercard1 be a pointer or not?


    /*
     *     MonsterCard( const std::string &cardName,int attackPoints, int defensePoints, int level, MonsterType type,
                 MonsterKind kind, MonsterAttribute attribute,bool active,Position position,bool alreadyAttack,
                 CardType cardType, CardLocation cardLocation, const std::string &cardDescription,bool summonedThisTurn = false);
    */


     MonsterCard* monsterCard1 = new MonsterCard("Sibirski Plavac", 3000, 2500, 4, MonsterType::DRAGON,
                                                 MonsterKind::NORMAL_MONSTER, MonsterAttribute::LIGHT,
                                                 true, Position::ATTACK, false,
                                                 CardType::MONSTER_CARD, CardLocation::HAND, "Opis", false
                                                );
     monsterCard1->setName("monsterCard1");

     scene->addItem(monsterCard1);
     scene->addWidget(monsterCard1->cardMenu);
     monsterCard1->move(300,300);
     // FIXME:Maybe this doesn't work because getHeight() returns height which is a private field of Card class so MonsterCard can't see it?
        // monsterCard1->setPos(0, scene->height() - monsterCard1->getHeight());

     // TODO: Make setting position not hardcoded:

     QPixmap background(":/resources/field2.png");
//     background = background.scaled(this->size(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
//     QPalette palette;
//     palette.setBrush(QPalette::Window, background);
     QBrush brush(QPalette::Window, background);
    //  ui->graphicsView->setBackgroundBrush(brush);

}

Game::Game() {}
Game::~Game() {
    delete ui;
    delete scene; // TODO: Check other memory deallocations too.
    // delete monsterCard1; // We can't free this here because it lives only in the constructor. !!
    // !! FIXME: Where do we free it then? Should it be initialized in the constructor or not?
}

GamePhases Game::getGamePhase() const
{
    return gamePhase;
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

    /*
     *  FIXME: This breaks the program, probably because we didn't call firstTurnSetup() yet,
     *  so m_pCurrentPlayer and m_pOtherPlayer have undefined values and can't be switched, leading to a SEGFAULT.
     */
    // In the end phase, we switch the players:
    //    switchPlayers();
}




