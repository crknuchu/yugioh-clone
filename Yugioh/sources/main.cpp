#include "headers/Card.h"
#include <iostream>

int main()
{

    Card karta("Dark magician",CardType::MonsterCard,CardPlace::Grave,"opis");
    std::cout << karta << std::endl;
    return 0;
}
