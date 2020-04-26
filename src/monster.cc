//
// Created by Aniruddha Pai on 4/26/20.
//

#include "zelda/monster.h"

namespace zelda {

Monster::Monster(Location location)
    : loc_{location} {}

void Monster::SetLoc(Location set_loc) { loc_ = set_loc; }

Location Monster::GetLoc() const { return loc_; }

} // namespace zelda