#include "headers/Game.h"
#include <iostream>
#include <random>

Game::Game(Player p1, Player p2) : m_p1(p1), m_p2(p2) {}
Game::Game() {}
Game::~Game() {}

enum class GamePhases {
  DRAW_PHASE,
  MAIN_PHASE1,
  BATTLE_PHASE,
  MAIN_PHASE2,
  END_PHASE
};

int Game::randomGenerator(const int limit) {
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

int Game::decideWhoPlaysFirst() { return randomGenerator(2); }

void Game::firstTurnSetup() {
  if (m_first == 1) {
    m_p1.drawCards(6);
    m_p2.drawCards(5);
  } else {
    m_p2.drawCards(6);
    m_p1.drawCards(5);
  }
}

void Game::start() {
  std::cout << "The game has started." << std::endl;

  int x; // Needed for now for the cin at the end of our while loop, will be removed when checkLifePoints is implemented.

  // Variable declarations/initializations:
  m_turnNumber = 1;
  GamePhases gamePhase;  // The are unused variable warnings for now because the implementation is not complete.

  while (true) {
    // The game decides who will play first:
    m_first = decideWhoPlaysFirst();
    std::cout << "The first player is " << m_first << std::endl;

    // Draw Phase begins:
    gamePhase = GamePhases::DRAW_PHASE;

    // In firstTurnSetup we give cards to the players:
    // TODO: Move this out of the loop to prevent unnecessary if checks that will never be true except in turn 1.
    if(m_turnNumber == 1)
        firstTurnSetup();

    // ...

    // After the cards are dealt, the draw phase ends and the main phase 1 begins:
    gamePhase = GamePhases::MAIN_PHASE1;

    // ...


    m_turnNumber++;

    /*
     *  For now, the game runs as an infinite loop (the cin is added as a blocking operation).
     *  checkLifePoints function will be implemented as the way to end the game.
     */
    std::cin >> x;
    std::cout << m_turnNumber << std::endl;
  }
  std::cout << "The game has ended." << std::endl;
}
