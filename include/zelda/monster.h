//
// Created by Aniruddha Pai on 4/26/20.
//

#ifndef FINALPROJECT_MONSTER_H
#define FINALPROJECT_MONSTER_H

#include "location.h"

namespace zelda {

//int monster_start_screen = 3;

class Monster {
 public:
  explicit Monster(Location location);

  // Sets the new location of the player
  void SetLoc(Location set_loc);

  // Gets the current location of the player
  Location GetLoc() const;

 private:
  Location loc_;
};

} // namespace zelda

#endif  // FINALPROJECT_MONSTER_H
