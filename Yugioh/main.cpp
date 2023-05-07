#include "headers/Card.h"
#include "headers/Game.h"
#include "headers/Monstercard.h"
#include "headers/Player.h"
#include <QApplication>
#include <iostream>

int main(int argc, char **argv) {
  QApplication app(argc, argv);

  Player player1("Nikola");
  Player player2("Milan");

  app.exec();
  return 0;
}
