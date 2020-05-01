//
// Created by Aniruddha Pai on 4/26/20.
//

#include "zelda/monster.h"
#include <zelda/map.h>

using zelda::Map;
using zelda::Direction;

namespace zelda {

int random_dir = 0;

Monster::Monster() {}

void Monster::SetUpMaps(Map maps) {
  map_screens_ = maps.GetScreen();
}


std::vector<Map> Monster::MoveMonster(int map_num) {}

} // namespace zelda