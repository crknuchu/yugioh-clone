#include "headers/Card.h"
#include "headers/Player.h"
#include "headers/Game.h"
#include <iostream>

int main()
{
  Player player1("Nikola");
  Player player2("Milan");

  Game game(player1, player2);
  game.start();



  Card karta("Dark magician",CardType::MonsterCard,CardPlace::Grave,"opis");
  std::cout << karta << std::endl;
  return 0;
}
