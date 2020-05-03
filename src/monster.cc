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

void Monster::SetIsPlayerAttack(bool set_is_player_attack) {
  is_player_attack_ = set_is_player_attack;
}

std::vector<Map> Monster::MoveMonster(Direction d, Location l, int map_num) {
  is_monster_move_ = false;

  if (IsMonstersAttacked(d, l, map_num)) {
    goto exitloops;
  }

  for (int i = 0; i < kMapHeight; i++) {
    for (int j = 0; j < kMapWidth; j++) {
      if (map_screens_[map_num].coordinates_[i][j] == monster_) {
        rand_direction = rand() % 4;

        if (rand_direction == 0) {
          if (map_screens_[map_num].coordinates_[i + 1][j] == empty_tile_) { //down
            map_screens_[map_num].coordinates_[i + 1][j] = monster_;
            map_screens_[map_num].coordinates_[i][j] = empty_tile_;
            is_monster_move_ = true;
          }
        } else if (rand_direction == 1) {
          if (map_screens_[map_num].coordinates_[i - 1][j] == empty_tile_) {  //up
            map_screens_[map_num].coordinates_[i - 1][j] = monster_;
            map_screens_[map_num].coordinates_[i][j] = empty_tile_;
            is_monster_move_ = true;
          }
        } else if (rand_direction == 2) {
          if (map_screens_[map_num].coordinates_[i][j - 1] == empty_tile_) {  //left
            map_screens_[map_num].coordinates_[i][j - 1] = monster_;
            map_screens_[map_num].coordinates_[i][j] = empty_tile_;
            is_monster_move_ = true;
          }
        } else if (rand_direction == 3) {
          if (map_screens_[map_num].coordinates_[i][j + 1] == empty_tile_) {  //right
            map_screens_[map_num].coordinates_[i][j + 1] = monster_;
            map_screens_[map_num].coordinates_[i][j] = empty_tile_;
            is_monster_move_ = true;
          }
        }
      }
    }
  }

  exitloops:;
  is_monster_attacked_ = false;
  return map_screens_;
}

bool Monster::IsMonstersAttacked(Direction d, Location l, int map_num) {
  int p_row = l.Col();
  int p_col = l.Row();

  if (is_player_attack_) {
    if (map_screens_[map_num].coordinates_[p_row - 1][p_col] == monster_ &&
        d == Direction::kUp) {
      map_screens_[map_num].coordinates_[p_row - 1][p_col] = empty_tile_;
      is_monster_attacked_ = true;
    } else if (map_screens_[map_num].coordinates_[p_row + 1][p_col] == monster_ &&
               d == Direction::kDown) {
      map_screens_[map_num].coordinates_[p_row + 1][p_col] = empty_tile_;
      is_monster_attacked_ = true;
    } else if (map_screens_[map_num].coordinates_[p_row][p_col - 1] == monster_ &&
               d == Direction::kLeft) {
      map_screens_[map_num].coordinates_[p_row][p_col - 1] = empty_tile_;
      is_monster_attacked_ = true;
    } else if (map_screens_[map_num].coordinates_[p_row][p_col + 1] == monster_ &&
               d == Direction::kRight) {
      map_screens_[map_num].coordinates_[p_row][p_col + 1] = empty_tile_;
      is_monster_attacked_ = true;
    } else if (map_screens_[map_num].coordinates_[p_row][p_col] == monster_) {
      map_screens_[map_num].coordinates_[p_row][p_col] = empty_tile_;
      is_monster_attacked_ = true;
    }
  }

  is_player_attack_ = false;
  return is_monster_attacked_;
}

bool Monster::IsMonsterMove() { return is_monster_move_; }

bool Monster::IsMonsterAttackLink(Location location, int map_num) {
  int p_row = location.Col();
  int p_col = location.Row();

  return map_screens_[map_num].coordinates_[p_row][p_col] == monster_;
}

} // namespace zelda