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

void Player::SetCurrentHealth(int set_current_health) {
  std::cout<<"set_current_health"<<set_current_health<<std::endl;
  current_health_ = set_current_health;
  std::cout<<"current_health_"<<current_health_<<std::endl;
}

int Player::GetCurrentHealth() { return current_health_; }

int count = 0;
void Player::AddInfoToMenu() {
  std::cout<<"Count "<<count++<<" Current Health "<<current_health_<<std::endl;

  json j;

  j = {
      {"Name: ", "Link"},
      {"Max Health: ", max_health_},
      {"Current Health", current_health_},
      {"Monsters Killed: ", monsters_killed_}
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