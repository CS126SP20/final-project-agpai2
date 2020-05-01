//
// Created by Aniruddha Pai on 4/26/20.
//

#ifndef FINALPROJECT_MONSTER_H
#define FINALPROJECT_MONSTER_H

#include "direction.h"
#include "location.h"
#include "map.h"

namespace zelda {

const int kMapHeight = 13;
const int kMapWidth = 21;

class Monster {
 public:
  Monster();

  // Moves the Monster
  std::vector<Map> MoveMonster(int map_num);

  void SetUpMaps(Map maps);

 private:
  std::vector<Map> map_screens_;
  char monster_ = 'M';
  char empty_tile_ = '0';

};

} // namespace zelda

#endif  // FINALPROJECT_MONSTER_H
