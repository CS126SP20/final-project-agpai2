//
// Created by Aniruddha Pai on 4/18/20.
//

#ifndef FINALPROJECT_PLAYER_H
#define FINALPROJECT_PLAYER_H

#include "location.h"

namespace zelda {

class Player {
 public:
  explicit Player(Location location);

  // Sets the new location of the player
  void SetLoc(Location set_loc);

  // Gets the current location of the player
  Location GetLoc() const;

  // Sets the current health of the player
  void SetCurrentHealth(int set_current_health);

  // Gets the current health of the player
  int GetCurrentHealth();

  // Add information to Menu
  void AddInfoToMenu();

  // To View the Menu screen
  void ViewMenu();

 private:
  Location loc_;

  int max_health_ = 3;
  int current_health_ = 3;
  int monsters_killed_ = 0;
};

} // namespace zelda

#endif  // FINALPROJECT_PLAYER_H
