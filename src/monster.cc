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

Direction Monster::GetMonsterDirection() { return monster_direction_; }

int Monster::GetMonstersKilled() { return monsters_killed_; }

bool Monster::IsMonstersAttacked(Direction d, Location l, int map_num) {
  int p_row = l.Col();
  int p_col = l.Row();

  if (is_player_attack_) {
    if (map_screens_[map_num].coordinates_[p_row - 1][p_col] == monster_ &&
        d == Direction::kUp) {
      map_screens_[map_num].coordinates_[p_row - 1][p_col] = empty_tile_;
      monsters_killed_++;
      is_monster_attacked_ = true;
    } else if (map_screens_[map_num].coordinates_[p_row + 1][p_col] == monster_ &&
               d == Direction::kDown) {
      map_screens_[map_num].coordinates_[p_row + 1][p_col] = empty_tile_;
      monsters_killed_++;
      is_monster_attacked_ = true;
    } else if (map_screens_[map_num].coordinates_[p_row][p_col - 1] == monster_ &&
               d == Direction::kLeft) {
      map_screens_[map_num].coordinates_[p_row][p_col - 1] = empty_tile_;
      monsters_killed_++;
      is_monster_attacked_ = true;
    } else if (map_screens_[map_num].coordinates_[p_row][p_col + 1] == monster_ &&
               d == Direction::kRight) {
      map_screens_[map_num].coordinates_[p_row][p_col + 1] = empty_tile_;
      monsters_killed_++;
      is_monster_attacked_ = true;
    } else if (map_screens_[map_num].coordinates_[p_row][p_col] == monster_) {
      map_screens_[map_num].coordinates_[p_row][p_col] = empty_tile_;
      monsters_killed_++;
      is_monster_attacked_ = true;
    }
  }

  is_player_attack_ = false;
  return is_monster_attacked_;
}

int slow_monster_move = 0;
std::vector<Map> Monster::MoveMonster(Direction d, Location l, int map_num) {
  slow_monster_move++;
  is_monster_move_ = false;

  if (IsMonstersAttacked(d, l, map_num)) {
    goto exit_loops;
  }

  if (slow_monster_move % kRowTiles == 0) {
    for (int i = 0; i < kColTiles; i++) {
      for (int j = 0; j < kRowTiles; j++) {
        if (map_screens_[map_num].coordinates_[i][j] == monster_) {
          rand_direction = rand() % 4;

          if (rand_direction == 0) {
            if (map_screens_[map_num].coordinates_[i + 1][j] ==
                empty_tile_) {  // down
              monster_direction_ = Direction::kDown;
              map_screens_[map_num].coordinates_[i + 1][j] = monster_;
              map_screens_[map_num].coordinates_[i][j] = empty_tile_;
              is_monster_move_ = true;
            }
          } else if (rand_direction == 1) {
            if (map_screens_[map_num].coordinates_[i - 1][j] ==
                empty_tile_) {  // up
              monster_direction_ = Direction::kUp;
              map_screens_[map_num].coordinates_[i - 1][j] = monster_;
              map_screens_[map_num].coordinates_[i][j] = empty_tile_;
              is_monster_move_ = true;
            }
          } else if (rand_direction == 2) {
            if (map_screens_[map_num].coordinates_[i][j - 1] ==
                empty_tile_) {  // left
              monster_direction_ = Direction::kLeft;
              map_screens_[map_num].coordinates_[i][j - 1] = monster_;
              map_screens_[map_num].coordinates_[i][j] = empty_tile_;
              is_monster_move_ = true;
            }
          } else if (rand_direction == 3) {
            if (map_screens_[map_num].coordinates_[i][j + 1] ==
                empty_tile_) {  // right
              monster_direction_ = Direction::kRight;
              map_screens_[map_num].coordinates_[i][j + 1] = monster_;
              map_screens_[map_num].coordinates_[i][j] = empty_tile_;
              is_monster_move_ = true;
            }
          }
        }
      }
    }
  }

  exit_loops:;
  is_monster_attacked_ = false;
  return map_screens_;
}

bool Monster::IsMonsterAttackLink(Location location, int map_num) {
  attack_delay_++;

  int p_row = location.Col();
  int p_col = location.Row();

  if (attack_delay_ % kColTiles == 0) {
    return map_screens_[map_num].coordinates_[p_row][p_col] == monster_;
  }
}

bool Monster::IsMonsterMove() { return is_monster_move_; }

bool Monster::IsPlayerAttack() { return is_player_attack_; }

} // namespace zelda