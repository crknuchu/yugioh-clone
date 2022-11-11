/* This is a placeholder Player class for now that will be properly implemented later
   All of the functions and fields are bound to change, and are in this current "placeholder state" because they are
   needed for the testing of the Game class.
*/
#ifndef PLAYER_H
#define PLAYER_H

#include <string>
class Player
{
public:
  Player();
  Player(std::string name);
  ~Player();


  // Public member functions:
  std::string getName();
  void drawCards(int n);

private:
  std::string m_name;
};

#endif // PLAYER_H
