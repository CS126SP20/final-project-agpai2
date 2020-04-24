//
// Created by Aniruddha Pai on 4/18/20.
//

#include "zelda/player.h"
#include <nlohmann/json.hpp>
#include <sqlite_modern_cpp.h>


namespace zelda {

Player::Player(Location location)
  : loc_{location} {}

void Player::SetLoc(Location set_loc) { loc_ = set_loc; }

Location Player::GetLoc() const { return loc_; }

} // namespace zelda