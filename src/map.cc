//
// Created by Aniruddha Pai on 4/21/20.
//

#include "zelda/map.h"

#include <fstream>
#include <string>
#include <vector>

using zelda::Direction;
using zelda::Location;

int prev_row = 0;
int prev_col = 0;

int cave_enter_count = 0;

namespace zelda {

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
      "/Users/aniruddhapai/Downloads/cinder_0.9.2_mac/finalproject/final-project-agpai2/assets/maplabels.txt";
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
      = "/Users/aniruddhapai/Downloads/cinder_0.9.2_mac/finalproject/final-project-agpai2/assets/zeldamaps.txt";
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

std::vector<Map> Map::GetScreen(){
  return game_maps_;
}

void Map::SetGameScreens(std::vector<Map> game_screens) {
  game_maps_ = std::move(game_screens);
}

bool Map::IsScreenChange() { return is_screen_change_; }

bool Map::IsSwordTaken() { return is_sword_taken_; }

int Map::GetNewScreenNum() { return screen_num_; }

Location Map::GetPlayerNewLoc(const Map& curr_map, Engine engine) {
  is_screen_change_ = false;

  Location location = engine.GetPlayer().GetLoc();

  int curr_row = location.Col();
  int curr_col = location.Row();

  if (curr_map.coordinates_[curr_row][curr_col] == char(t)) {
    is_sword_taken_ = true;
    screen_num_ = kScreen2;
    return location;
  }

  if (curr_map.coordinates_[curr_row][curr_col] == char(a) &&
      engine.GetDirection() == Direction::kUp) {
    if (!is_sword_taken_) {
      screen_num_ = kScreen3;
    } else {
      screen_num_ = kScreen2;
    }
    is_screen_change_ = true;
    return {kLocPosOne,kLocPosOne + 1};
  } else if (curr_map.coordinates_[curr_row][curr_col] == char(a) &&
             engine.GetDirection() == Direction::kDown) {
    screen_num_ = kScreen1;
    is_screen_change_ = true;
    return {kLocPosTwo, kLocPosThree};
  }

  for (int j = 0; j < entry_points_.size(); j++) {
    if (curr_map.coordinates_[curr_row][curr_col] == entry_points_.at(j)) {
      screen_num_ = GetTransitionScreenNum(GetCurrScreenNum(curr_map),
          entry_points_.at(j));

      is_screen_change_ = true;
      if (engine.GetDirection() == Direction::kUp) {
        return {curr_col,kLocPosOne + 1};
      } else if (engine.GetDirection() == Direction::kDown) {
        return {curr_col,1};
      } else if (engine.GetDirection() == Direction::kLeft) {
        return {kRowWidth - kLocPosThree, curr_row};
      } else if (engine.GetDirection() == Direction::kRight) {
        return {1, curr_row};
      }
    }
  }
  Location new_loc = CheckForCaveEntry(curr_map, engine);

  return new_loc;
}

Location Map::CheckForCaveEntry(const Map& curr_map, Engine engine) {
  is_screen_change_ = false;

  Location location = engine.GetPlayer().GetLoc();

  int curr_row = location.Col();
  int curr_col = location.Row();

  for (int i = 0; i < cave_entry_points_.size(); i++) {
    if (curr_map.coordinates_[curr_row][curr_col] == cave_entry_points_.at(i)) {
      screen_num_ = GetTransitionScreenNum(GetCurrScreenNum(curr_map),
          cave_entry_points_.at(i));
      is_screen_change_ = true;
      if (cave_enter_count == 0) {
        cave_enter_count++;
        is_cave_enter_ = true;
      }

      if (is_cave_enter_) {
        is_cave_enter_ = false;
        prev_row = curr_row + 1;
        prev_col = curr_col;
        return {kLocPosOne, kLocPosOne + 1};
      } else {
        cave_enter_count = 0;
        return {prev_col, prev_row};
      }
    }
  }

  return location;
}

int Map::GetCurrScreenNum(const Map& curr_map) {
  int count = 0;

  for (int i = 0; i < game_maps_.size(); i++) {
    for (int j = 0; j < kColumnHeight; j++) { // 13
      for (int k = 0; k < kRowWidth; k++) {  // 21
        if (game_maps_[i].coordinates_[j][k] == curr_map.coordinates_[j][k]) {
          count++;
        } else {
          count = 0;
          // If the screens are not equal, the outer-loop is called
          goto outerloop;
        }
        if (count == kRowWidth * kColumnHeight) {
          return i;
        }
      }
    }
    outerloop:;
  }
}

int Map::GetTransitionScreenNum(int num, char entry) {

  for (int i = 0; i < game_maps_.size(); i++) {
    if (i != num) {
      for (int j = 0; j < kColumnHeight; j++) {
        for (int k = 0; k < kRowWidth; k++) {
          // This is to check for other maps having the same entry/exit points
          if (game_maps_[i].coordinates_[j][k] == entry) {
            return i;
          }
        }
      }
    }
  }
}

} // namespace zelda
