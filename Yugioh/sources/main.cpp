#include "headers/mainmenu.h"
#include <iostream>

#include "headers/mainmenu.h"
#include <QApplication>
#include <iostream>

auto main(int argc, char **argv) -> int {
  QApplication app(argc, argv);

  MainMenu m;

  // MainMenu m;
  m.showFullScreen();

  return app.exec();
}
