//
// Created by Aniruddha Pai on 4/18/20.
//

#ifndef FINALPROJECT_PLAYER_H
#define FINALPROJECT_PLAYER_H

#include "location.h"

namespace mylibrary {

class Player {
 public:
  Player(Location location) : loc(location) {}

  void SetLoc (Location set_loc) {
    loc = set_loc;
  }

  Location GetLoc() const { return loc;}

 private:
  Location loc;
};

}

#endif  // FINALPROJECT_PLAYER_H
