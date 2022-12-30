#include "headers/mainmenu.h"
#include "headers/Serializer.h"
#include <iostream>
#include <QApplication>




int main(int argc,char **argv)
{
    QApplication app(argc, argv);

    MainMenu m;
    Serializer s1;
    Serializer s2;
    s1.loadFromJson(":/resources/yugi.json");
    s2.loadFromJson(":/resources/yugi.json");
    Player* player1 = new Player("Nikola");
    Player* player2 = new Player("Milan");
    std::vector<Card*> yugiCards1 = s1.getCards();
    std::vector<Card*> yugiCards2 = s2.getCards();
    Deck d1 = Deck(yugiCards1);
    Deck d2 = Deck(yugiCards2);
    player1->setDeck(d1);
    player2->setDeck(d2);
    Game* game = new Game(*player1, *player2);
    game->showFullScreen();

    return app.exec();
}
