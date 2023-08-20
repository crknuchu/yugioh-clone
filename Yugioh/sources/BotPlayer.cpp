#include "headers/BotPlayer.h"

BotPlayer::BotPlayer() = default;

BotPlayer::BotPlayer(std::string name, int points) : Player(name, points) {
  std::cout << "Bot has been initialized" << std::endl;
}

auto BotPlayer::randomGenerator(const int limit) const -> int {
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

auto BotPlayer::decideToPlay() -> bool {
  return BotPlayer::randomGenerator(2) % 2 == 0;
}
