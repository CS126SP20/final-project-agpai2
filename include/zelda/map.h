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

// These are constants that represent the dimensions of the screen
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

  // Sets all the Maps/Screens of a game
  void SetGameScreens(std::vector<Map> game_screens);

  // Gets all the Maps/Screens of a game
  std::vector<Map> GetScreen();

  // Gets the labels of the maps/screens
  std::string GetMapLabels();

  // Gets the map or screen number link is planning to enter
  int GetNewScreenNum();

  // Reads through all the image labels in a file
  void ReadImageLabels();

  // Sets Up the Map
  void SetUpMap(std::string map_line);

  // Reads through all the game screens in a file
  void ReadGameScreens();

  // Gets the positional value of a map the player is in
  int GetCurrScreenNum(const Map& curr_map);

  // Gets the screen number of the screen to transition into
  int GetTransitionScreenNum(int num, char entry);

  // Gets the number of the new cave screen
  Location CheckForCaveEntry(const Map& curr_map, Engine engine);

  // Gets the new location of player after screen change
  Location GetPlayerNewLoc(const Map& curr_map, Engine engine);

  // Returns a bool value to check if the screen is changed
  bool IsScreenChange();

  // Returns a bool value to check if the sword is taken
  bool IsSwordTaken();

  // Contains different game screens
  enum GameScreens { kScreen1, kScreen2, kScreen3 };

  // Contains different entry points
  enum EntryPoints { a = 97, b, c, d, e, f, g, h, i, j, k, l, m,
    n, o, p, q, r, s, t, u, v, w, x, y, z};

  Direction direction;

 private:
  int screen_num_{};

  // Contains all the map labels
  std::vector<std::string> map_labels_;

  // Contains all the game screens
  std::vector<zelda::Map> game_maps_;

  // Contains a single game screen
  std::vector<std::vector<char>> map_;

  // These are entry points to different screens and caves
  std::string entry_points_ = "abcdefghijklmnopqrsdtuvwxyz";
  std::string cave_entry_points_ = "`~!@#$%^&*()_-+=[{}]|;:',<>.?/";

  // These are a set of bool values to check if the screen or cave has been
  // entered, or if the sword has been taken
  bool is_screen_change_ = false;
  bool is_sword_taken_ = false;
  bool is_cave_enter_ = false;
};

} // namespace zelda

#endif  // FINALPROJECT_MAP_H
