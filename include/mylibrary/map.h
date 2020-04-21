//
// Created by Aniruddha Pai on 4/21/20.
//

#ifndef FINALPROJECT_MAP_H
#define FINALPROJECT_MAP_H

#include <vector>

namespace mylibrary {

constexpr int row_width = 21;
constexpr int column_height = 13;

class Map {
 public:
  char coordinates_[column_height][row_width];  // 13, 21

 public:
  Map();
  explicit Map(std::vector<std::vector<char>> game_screen);
};

}
#endif  // FINALPROJECT_MAP_H
