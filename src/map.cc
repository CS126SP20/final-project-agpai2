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

void Map::ReadImageLabels() {
  std::string map_label_file =
      "/Users/aniruddhapai/Downloads/cinder_0.9.2_mac/finalproject/zelda-trials/assets/maplabels.txt";
  std::ifstream file(map_label_file);

  while (!file.eof()) {
    std::string map_label;
    getline(file, map_label);
    map_labels_.push_back(map_label);
  }
}

void Map::ReadGameScreens() {
  int map_line_count = 0;

  std::string maps_file
      = "/Users/aniruddhapai/Downloads/cinder_0.9.2_mac/finalproject/zelda-trials/assets/zeldamaps.txt";
  std::ifstream file(maps_file);

  while (!file.eof()) {
    std::string map_line;
    getline(file, map_line);
    if (!map_line.empty()) {
      SetUpMap(map_line);
      map_line_count++;

      if (map_line_count == kColumnHeight) {
        Map game_screen = Map(map_);
        game_maps_.push_back(game_screen);
        map_line_count = 0;
        map_.clear();
      }
    }
  }
}

void Map::SetUpMap(std::string map_line) {
  std::vector<char> map_line_char;

  // This is done to pre-allocate a set memory to every line of a map
  map_line_char.reserve(kRowWidth);
  for (int i = 0; i < kRowWidth; i++) {
    map_line_char.push_back(map_line.at(i));
  }

  map_.push_back(map_line_char);
}

std::string Map::GetMapLabels() {
  for (int i = 0; i < map_labels_.size(); i++) {
    if (i == screen_num_) {
      return map_labels_[i];
    }
  }
}

std::vector<Map> Map::GetScreen(){ return game_maps_; }

bool Map::IsScreenChange() { return is_screen_change; }

int Map::GetGameScreenNum() { return screen_num_; }

Location Map::GetPlayerNewLoc(const Map& curr_map, Engine engine) {

  Location location = engine.GetPlayer().GetLoc();

  int curr_row = location.Col();
  int curr_col = location.Row();

  if (curr_map.coordinates_[curr_row][curr_col] == 'a' &&
      engine.GetDirection() == Direction::kUp) {
    screen_num_ = kScreen2;
    is_screen_change = true;
    return {kLocPosOne,kLocPosOne + 1};
  } else if (curr_map.coordinates_[curr_row][curr_col] == 'a' &&
             engine.GetDirection() == Direction::kDown) {
    screen_num_ = kScreen1;
    is_screen_change = true;
    return {kLocPosTwo, kLocPosThree};
  }

  if (curr_map.coordinates_[curr_row][curr_col] == 'b' &&
      engine.GetDirection() == Direction::kUp) {
    screen_num_ = kScreen3;
    is_screen_change = true;
    return {kLocPosOne,kLocPosOne + 1};
  } else if (curr_map.coordinates_[curr_row][curr_col] == 'b' &&
             engine.GetDirection() == Direction::kDown) {
    screen_num_ = kScreen1;
    is_screen_change = true;
    return {kLocPosOne,0};
  }

  is_screen_change = false;
  return location;
}

}
