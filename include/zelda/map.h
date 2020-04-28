//
// Created by Aniruddha Pai on 4/21/20.
//

#ifndef FINALPROJECT_MAP_H
#define FINALPROJECT_MAP_H

#include <zelda/engine.h>

#include <string>
#include <vector>

using zelda::Engine;

namespace zelda {

constexpr int kRowWidth = 21;
constexpr int kColumnHeight = 13;

// These are the constants for changing Link's position
const int kLocPosOne = 10;
const int kLocPosTwo = 5;
const int kLocPosThree = 2;

class Map {
 public:
  char coordinates_[kColumnHeight][kRowWidth]{};  // 13, 21

 public:
  Map();
  explicit Map(std::vector<std::vector<char>> game_screen);

  // Gets the new location of player after screen change
  Location GetPlayerNewLoc(const Map& curr_map, Engine engine);

  // Gets the number of the new cave screen
  Location CheckForCaveEntry(const Map& curr_map, Engine engine);

  // Gets the labels of the maps/screens
  std::string GetMapLabels();

  // Reads through all the image labels in a file
  void ReadImageLabels();

  // Reads through all the game screens in a file
  void ReadGameScreens();

  // Sets Up the Map
  void SetUpMap(std::string map_line);

  // Returns a bool value to check if the screen is changed
  bool IsScreenChange();

  // Returns a bool value to check if the sword is taken
  bool IsSwordTaken();

  // Gets the positional value of a map the player is in
  int GetCurrScreenNum(const Map& curr_map);

  // Gets the map or screen number link is planning to enter
  int GetNewScreenNum();

  // Gets the screen number of the screen to transition into
  int GetTransitionScreenNum(int num, char entry);

  // Gets all the Maps/Screens of a game
  std::vector<Map> GetScreen();

  // Contains different game screens
  enum GameScreens { kScreen1, kScreen2, kScreen3 };

  // Contains different entry points
  enum EntryPoints { a = 97, b, c, d, e, f, g, h, i, j, k, l, m,
    n, o, p, q, r, s, t, u, v, w, x, y, z};

 private:
  int screen_num_{};
  std::vector<std::string> map_labels_;

  bool is_screen_change_ = false;

  bool is_sword_taken_ = false;

  bool is_cave_enter_ = false;

  //Contains all the game screens
  std::vector<zelda::Map> game_maps_;
  // Contains a single game screen
  std::vector<std::vector<char>> map_;

  std::string entry_points_ = "abcdefghijklmnopqrsdtuvwxyz";
  std::string cave_entry_points_ = "`~!@#$%^&*()_-+=[{}]|;:',<>.?/";
};

} // namespace zelda

#endif  // FINALPROJECT_MAP_H
