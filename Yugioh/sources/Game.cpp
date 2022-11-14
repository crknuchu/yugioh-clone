#include "headers/Game.h"
#include <iostream>
#include <random>

Game::Game(Player p1, Player p2) : m_player1(p1), m_player2(p2) {}
Game::Game() {}
Game::~Game() {}

enum class GamePhases {
  DRAW_PHASE,
  STANDBY_PHASE,
  MAIN_PHASE1,
  BATTLE_PHASE,
  MAIN_PHASE2,
  END_PHASE
};

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

  std::cout << "The first one to play is " << m_pCurrentPlayer->getName() << std::endl;

  // The first one gets 6 cards:
  m_pCurrentPlayer->drawCards(6);

  // The other one gets 5 cards
  // Without m_pOtherPlayer:  *m_pCurrentPlayer == m_player1 ? m_player2.drawCards(5) : m_player1.drawCards(5);
  // With m_pOtherPlayer:
  m_pOtherPlayer->drawCards(5);
}

void Game::start() {
  std::cout << "The game has started." << std::endl;

  int x; // Needed for now for the cin at the end of our while loop, will be removed when checkLifePoints is implemented.

  // First turn is special (there is no battle phase and main phase 2):
  GamePhases gamePhase = GamePhases::DRAW_PHASE;
  m_turnNumber = 1;
  firstTurnSetup();

  gamePhase = GamePhases::STANDBY_PHASE;
  // ...

  gamePhase = GamePhases::MAIN_PHASE1;

  /*
   *  Placeholder for the first turn's loop.
   *  Since the player action mechanisms are still not implemented (TODO),
   *  for now we only have a while loop that instantly finishes.
   */
  while(gamePhase != GamePhases::END_PHASE)
  {
    /*
     *  Here the firstPlayer will play his MainPhase1 in the first turn.
     *  For now, we still don't have playMP1() implemented.
     */

     gamePhase = GamePhases::END_PHASE;
  }

  m_turnNumber++;

  while (true)
  {
    switchPlayers();
    std::cout << "The current player is " << m_pCurrentPlayer->getName() << "." << std::endl;
    // Draw Phase begins:
    gamePhase = GamePhases::DRAW_PHASE;

    // The current player draws a card (this is not optional).
    m_pCurrentPlayer->drawCards(1);


    // The draw phase ends and the standby phase begins (this is not optional).
    gamePhase = GamePhases::STANDBY_PHASE;
    // ...

    // The standby phase ends and the main phase 1 begins (this is not optional).
    gamePhase = GamePhases::MAIN_PHASE1;
    // ...


    // The battle phase is optional.
    // Placeholder pseudo-code for event listening:
    /*
     * if BP button was clicked                     // TODO
     * then gamePhase = GamePhases::BATTLE_PHASE;
     * ...
    */


    /* We (optionally) enter the MP2 only if there was a battle phase
     * and the MP2 button was clicked (TODO) */
    if (gamePhase == GamePhases::BATTLE_PHASE)
    {
        gamePhase = GamePhases::MAIN_PHASE2;
        // ...
    }

    // The end phase begins if the EP button was clicked (TODO):
    gamePhase = GamePhases::END_PHASE;
    // ...

    m_turnNumber++;

    /*
     *  For now, the game runs as an infinite loop (the cin is added as a blocking operation).
     *  checkLifePoints function will be implemented as the way to end the game.
     */
    std::cin >> x;

  }
  std::cout << "The game has ended." << std::endl;
}
