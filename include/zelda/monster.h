//
// Created by Aniruddha Pai on 4/26/20.
//

#ifndef FINALPROJECT_MONSTER_H
#define FINALPROJECT_MONSTER_H

#include "direction.h"
#include "location.h"
#include "map.h"

namespace zelda {

class Monster {
 public:
  Monster();

  // Moves the Monster
  std::vector<Map> MoveMonster(int map_num);

  void SetUpMaps(Map maps);

 private:
  std::vector<Map> map_screens_;
  char monster = 'M';

};

} // namespace zelda

#endif  // FINALPROJECT_MONSTER_H
