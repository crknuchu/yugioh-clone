#include "headers/Game.h"
#include "headers/Player.h"
#include <iostream>


int main() {
  Player player1("Nikola");
  Player player2("Milan");

  Game game(player1, player2);
  game.start();

  return 0;
}
