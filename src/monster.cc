//
// Created by Aniruddha Pai on 4/26/20.
//

#include "zelda/monster.h"
#include <zelda/map.h>

using zelda::Map;
using zelda::Direction;

namespace zelda {

int rand_direction = 0;

Monster::Monster() {}

void Monster::SetUpMaps(Map maps) {
  map_screens_ = maps.GetScreen();
}


std::vector<Map> Monster::MoveMonster(int map_num) {

  for (int i = 0; i < kMapHeight; i++) {
    for (int j = 0; j < kMapWidth; j++) {
      if (map_screens_[map_num].coordinates_[i][j] == monster_) {
        rand_direction = rand() % 4;

        if (rand_direction == static_cast<int>(Direction::kDown)) {
          if (map_screens_[map_num].coordinates_[i + 1][j] == empty_tile_) { //down
            map_screens_[map_num].coordinates_[i + 1][j] = monster_;
            map_screens_[map_num].coordinates_[i][j] = empty_tile_;
          }
        } else if (rand_direction == static_cast<int>(Direction::kUp)) {
          if (map_screens_[map_num].coordinates_[i - 1][j] == empty_tile_) {  //up
            map_screens_[map_num].coordinates_[i - 1][j] = monster_;
            map_screens_[map_num].coordinates_[i][j] = empty_tile_;
          }
        } else if (rand_direction == static_cast<int>(Direction::kLeft)) {
          if (map_screens_[map_num].coordinates_[i][j - 1] == empty_tile_) {  //left
            map_screens_[map_num].coordinates_[i][j - 1] = monster_;
            map_screens_[map_num].coordinates_[i][j] = empty_tile_;
          }
        } else if (rand_direction == static_cast<int>(Direction::kRight)) {
          if (map_screens_[map_num].coordinates_[i][j + 1] == empty_tile_) {  //right
            map_screens_[map_num].coordinates_[i][j + 1] = monster_;
            map_screens_[map_num].coordinates_[i][j] = empty_tile_;
          }
        }
      }
    }
  }

  return map_screens_;
}

} // namespace zelda