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

  // Add information to Menu
  void AddInfoToMenu();

  // To View the Menu screen
  void ViewMenu();

 private:
  Location loc_;
};

} // namespace zelda

#endif  // FINALPROJECT_PLAYER_H
