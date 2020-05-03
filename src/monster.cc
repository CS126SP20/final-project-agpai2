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

  if (CheckIfMonstersAttacked(d, l, map_num)) {
    goto exitloops;
  }

  for (int i = 0; i < kMapHeight; i++) {
    for (int j = 0; j < kMapWidth; j++) {
      if (map_screens_[map_num].coordinates_[i][j] == 'M') {
        rand_direction = rand() % 4;

        if (rand_direction == 0) {
          if (map_screens_[map_num].coordinates_[i + 1][j] == '0') { //down
            map_screens_[map_num].coordinates_[i + 1][j] = 'M';
            map_screens_[map_num].coordinates_[i][j] = '0';
            is_monster_move_ = true;
          }
        } else if (rand_direction == 1) {
          if (map_screens_[map_num].coordinates_[i - 1][j] == '0') {  //up
            map_screens_[map_num].coordinates_[i - 1][j] = 'M';
            map_screens_[map_num].coordinates_[i][j] = '0';
            is_monster_move_ = true;
          }
        } else if (rand_direction == 2) {
          if (map_screens_[map_num].coordinates_[i][j - 1] == '0') {  //left
            map_screens_[map_num].coordinates_[i][j - 1] = 'M';
            map_screens_[map_num].coordinates_[i][j] = '0';
            is_monster_move_ = true;
          }
        } else if (rand_direction == 3) {
          if (map_screens_[map_num].coordinates_[i][j + 1] == '0') {  //right
            map_screens_[map_num].coordinates_[i][j + 1] = 'M';
            map_screens_[map_num].coordinates_[i][j] = '0';
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

bool Monster::CheckIfMonstersAttacked(Direction d, Location l, int map_num) {
  int p_row = l.Col();
  int p_col = l.Row();

  if (is_player_attack_) {
    if (map_screens_[map_num].coordinates_[p_row - 1][p_col] == 'M' &&
        d == Direction::kUp) {
      map_screens_[map_num].coordinates_[p_row - 1][p_col] = '0';
      is_monster_attacked_ = true;
    } else if (map_screens_[map_num].coordinates_[p_row + 1][p_col] == 'M' &&
               d == Direction::kDown) {
      map_screens_[map_num].coordinates_[p_row + 1][p_col] = '0';
      is_monster_attacked_ = true;
    } else if (map_screens_[map_num].coordinates_[p_row][p_col - 1] == 'M' &&
               d == Direction::kLeft) {
      map_screens_[map_num].coordinates_[p_row][p_col - 1] = '0';
      is_monster_attacked_ = true;
    } else if (map_screens_[map_num].coordinates_[p_row][p_col + 1] == 'M' &&
               d == Direction::kRight) {
      map_screens_[map_num].coordinates_[p_row][p_col + 1] = '0';
      is_monster_attacked_ = true;
    } else if (map_screens_[map_num].coordinates_[p_row][p_col] == 'M') {
      map_screens_[map_num].coordinates_[p_row][p_col] = '0';
      is_monster_attacked_ = true;
    }
  }

  is_player_attack_ = false;
  return is_monster_attacked_;
}

bool Monster::IsMonsterMove() { return is_monster_move_; }

} // namespace zelda