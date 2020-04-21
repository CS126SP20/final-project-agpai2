//
// Created by Aniruddha Pai on 4/21/20.
//


#include "mylibrary/map.h"

#include <vector>

namespace mylibrary {

Map::Map() = default;

Map::Map(std::vector<std::vector<char>> game_screen) {  // 13, 21
  for (int i = 0; i < column_height; i++) {  //13
    for (int j = 0; j < row_width; j++) {  //21
      this->coordinates_[i][j] = game_screen[i][j];
    }
  }
}

}
