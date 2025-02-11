//
// Created by Aniruddha Pai on 4/26/20.
//

#ifndef FINALPROJECT_MONSTER_H
#define FINALPROJECT_MONSTER_H

#include "direction.h"
#include "location.h"
#include "map.h"

namespace zelda {

// These constants are the number of tiles in a row and column of a screen
const int kColTiles = 13;
const int kRowTiles = 21;

class Monster {
 public:
  Monster();

  // Sets up the game screens for all monsters
  void SetUpMaps(Map maps);

  // Sets the bool value when the player attacks
  void SetIsPlayerAttack(bool set_is_player_attack);

  // Gets the direction the monster is facing
  Direction GetMonsterDirection();

  // Gets the number of monsters killed
  int GetMonstersKilled();

  // Returns a bool value indicating if the monster was attacked
  bool IsMonstersAttacked(Direction d, Location l, int map_num);

  // Moves the Monster
  std::vector<Map> MoveMonster(Direction d, Location l, int map_num);

  // Returns a bool value based on if the monster has attacked Link
  bool IsMonsterAttackLink(Location location, int map_num);

  // Returns a bool value to check for monster movement
  bool IsMonsterMove();

  // Returns a bool value based on if the player has attacked the monster
  bool IsPlayerAttack();

 private:
  std::vector<Map> map_screens_;

  char monster_ = 'M';
  char empty_tile_ = '0';

  Direction monster_direction_;
  bool is_monster_move_ = false;

  int monsters_killed_ = 0;
  bool is_monster_attacked_ = false;

  bool is_player_attack_ = false;

  int attack_delay_ = 0;
};

} // namespace zelda

#endif  // FINALPROJECT_MONSTER_H
