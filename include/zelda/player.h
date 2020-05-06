//
// Created by Aniruddha Pai on 4/18/20.
//

#ifndef FINALPROJECT_PLAYER_H
#define FINALPROJECT_PLAYER_H

#include "location.h"

#include <string>

namespace zelda {

const int kRatio = 20;

// These constants are maintained to set bounds of a text box
// in player inventory
const int kXi[5] = {345, 345, 357, 1005, 1037};
const int kXj[5] = {1325, 1325, 1337, 1985, 2027};
const int kYi[5] = {65, 255, 432, 743, 623};
const int kYj[5] = {130, 320, 497, 808, 688};

class Player {
 public:
  explicit Player(Location location);

  // Sets the new location of the player
  void SetLoc(Location set_loc);

  // Gets the current location of the player
  Location GetLoc() const;

  // Sets the name of the player
  void SetPlayerName(std::string set_player_name);

  // Sets the current health of the player
  void SetCurrentHealth(int set_current_health);

  // Gets the current health of the player
  int GetCurrentHealth();

  // Sets the amount of money the player has
  void SetMoneyAmount(int set_money_amount);

  // Gets the amount of money the player has
  int GetMoneyAmount();

  // Sets the number of monsters killed
  void SetMonstersKilled(int monsters_killed);

  // Add information to Menu
  void AddInfoToMenu();

  // To View the Menu screen
  void ViewMenu();

 private:
  Location loc_;

  std::string player_name_;

  int max_health_ = 3;
  int current_health_ = 3;
  int monsters_killed_ = 0;
  int total_money_ = 0;
};

} // namespace zelda

#endif  // FINALPROJECT_PLAYER_H
