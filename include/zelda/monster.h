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

  // Sets up the game screens for all monsters
  void SetUpMaps(Map maps);

  // Returns a bool value to check for monster movement
  bool IsMonsterMove();

 private:
  std::vector<Map> map_screens_;
  char monster_ = 'M';
  char empty_tile_ = '0';

  bool is_monster_move_ = false;

};

} // namespace zelda

#endif  // FINALPROJECT_MONSTER_H
