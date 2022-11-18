#ifndef PLAYER_H
#define PLAYER_H

#include <string>
#include <iostream>
#include <memory>

class Player{ 

public:
    Player() = default;
    ~Player() {

    };
    Player(std::string player_name, int points = 4000) : name(player_name), points(points){};

    //TODO 
    //implement deck


    //implement hand cards

    //implement graveyard


    std::string get_player_name();
    unsigned get_player_points();


private:
    std::string name;
    unsigned points;
};

// std::istream &operator>>(std::istream &in, Player &p);
std::ostream &operator<<(std::ostream &out, Player &p);
#endif