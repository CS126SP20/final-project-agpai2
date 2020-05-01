//
// Created by Aniruddha Pai on 4/18/20.
//

#include <fstream>
#include <iomanip>

#include "zelda/player.h"
#include <nlohmann/json.hpp>
#include <sqlite_modern_cpp.h>

using nlohmann::json;

namespace zelda {

Player::Player(Location location)
  : loc_{location} {}

void Player::SetLoc(Location set_loc) { loc_ = set_loc; }

Location Player::GetLoc() const { return loc_; }

void Player::AddInfoToMenu() {
  json j;

  j = {
      {"Name: ", "Link"},
      {"Inventory Count: ", inventory_count_},
      {"Monster Kills: ", monsters_killed_},
  };

  std::ofstream add_to_menu("menu.json");
  add_to_menu << std::setw(4) << j << std::endl;
}

void Player::ViewMenu() {
  std::ifstream read_menu("menu.json");

  json j;
  read_menu >> j;

  for (json::iterator it = j.begin(); it != j.end(); ++it) {
    std::cout << *it << std::endl;
  }
}

} // namespace zelda