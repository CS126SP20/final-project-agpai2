//
// Created by Aniruddha Pai on 4/18/20.
//

#include <iostream>
#include <fstream>
#include <iomanip>

#include "zelda/player.h"
#include <nlohmann/json.hpp>

using namespace std;
using nlohmann::json;

namespace zelda {

Player::Player(Location location)
  : loc_{location} {}

void Player::SetLoc(Location set_loc) { loc_ = set_loc; }

Location Player::GetLoc() const { return loc_; }

void Player::SetCurrentHealth(int set_current_health) {
  cout << "set_current_health" << set_current_health << endl;
  current_health_ = set_current_health;
  cout << "current_health_" << current_health_ << endl;
}

int Player::GetCurrentHealth() { return current_health_; }

void Player::SetMonstersKilled(int monsters_killed) {
  monsters_killed_ = monsters_killed;
}

int count = 0;
void Player::AddInfoToMenu() {
  cout << "Count "<< count++ << " Current Health " << current_health_ << endl;

  json j;

  j = {
      {"Name: ", "Link"},
      {"Max Health: ", max_health_},
      {"Current Health", current_health_},
      {"Monsters Killed: ", monsters_killed_}
  };

  ofstream add_to_menu("menu.json");
  add_to_menu << setw(4) << j << endl;
}

void Player::ViewMenu() {
  ifstream read_menu("menu.json");

  json j;
  read_menu >> j;

  for (json::iterator it = j.begin(); it != j.end(); ++it) {
    cout << *it << endl;
  }
}

} // namespace zelda