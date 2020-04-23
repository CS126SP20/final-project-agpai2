//
// Created by Aniruddha Pai on 4/21/20.
//


#include "mylibrary/map.h"

#include <fstream>
#include <string>
#include <vector>

using mylibrary::Direction;
using mylibrary::Location;

namespace mylibrary {

Map::Map() = default;

Map::Map(std::vector<std::vector<char>> game_screen) {  // 13, 21
  for (int i = 0; i < kColumnHeight; i++) {             // 13
    for (int j = 0; j < kRowWidth; j++) {               // 21
      this->coordinates_[i][j] = game_screen[i][j];
    }
  }
}

void Map::ReadImageLabels() {}

void Map::ReadGameScreens() {}

void Map::SetUpMap(std::string map_line) {}

std::string Map::GetMapLabels() {}

std::vector<Map> Map::GetScreen(){ return game_maps_; }

bool Map::IsScreenChange() { return is_screen_change; }

int Map::GetGameScreenNum() { return screen_num_; }

Location Map::GetPlayerNewLoc(const Map& curr_map, Engine engine) {}

}
