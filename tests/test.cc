// Copyright (c) 2020 CS126SP20. All rights reserved.

#define CATCH_CONFIG_MAIN

#include <cinder/Rand.h>

#include <catch2/catch.hpp>
#include <nlohmann/json.hpp>
#include <fstream>

#include "../include/zelda/location.h"
#include "../include/zelda/engine.h"
#include "../include/zelda/direction.h"
#include "../include/zelda/player.h"
#include "../include/zelda/monster.h"
#include "../include/zelda/map.h"

using zelda::Location;
using zelda::Engine;
using zelda::Direction;
using zelda::Player;
using zelda::Monster;
using zelda::Map;

std::vector<std::vector<char>> sample_screen = {{ '1','1','1','p','p','1','p','p','1','p','p','p','1','p','1','p','p','1','p','1','1'},
                                                { '1','1','1','0','0','1','0','0','1','0','0','0','1','0','1','0','0','1','0','1','1'},
                                                { '1','1','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','1','1'},
                                                { '1','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','1','1'},
                                                { 'h','0','0','0','0','1','0','0','0','0','0','0','1','0','0','0','0','1','0','1','1'},
                                                { 'h','0','1','0','0','0','0','0','0','0','0','0','0','M','0','0','0','0','0','0','j'},
                                                { 'h','0','0','0','0','1','0','1','1','0','0','1','1','0','1','0','0','1','0','0','j'},
                                                { 'h','0','!','!','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','j'},
                                                { 'h','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','j'},
                                                { '1','0','0','0','0','1','0','0','0','0','0','0','1','0','0','0','0','1','0','1','1'},
                                                { '1','1','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','1','1'},
                                                { '1','1','1','1','0','1','0','1','1','0','0','1','1','0','1','0','0','1','0','1','1'},
                                                { '1','1','1','1','e','1','e','e','1','e','e','e','1','e','1','e','e','1','e','1','1'}};

Map sample_map = Map(sample_screen);

TEST_CASE("Location vector operations", "[location]") {
  SECTION("Modulo positive") {
    Location loc1{12, 9};
    Location loc2{7, 3};

    Location result = loc1 % loc2;
    REQUIRE(result == Location{5, 0});
  }

  SECTION("Modulo positive") {
    Location loc1{-1, 3};
    Location loc2{7, 2};

    Location result = loc1 % loc2;
    REQUIRE(result == Location{6, 1});
  }

  SECTION("Add Locations") {
    Location loc1{4, 3};
    Location loc2{2, 5};

    Location result = loc1 + loc2;
    REQUIRE(result == Location{6, 8});
  }
}

TEST_CASE("Location Values", "[location]") {
  Location loc{6, 10};

  SECTION("Row of Location") {
    int row_result = loc.Row();
    REQUIRE(row_result == 6);
  }

  SECTION("Column of Location") {
    int column_result = loc.Col();
    REQUIRE(column_result == 10);
  }
}

TEST_CASE("Change in Directions", "[engine-constructor][direction]") {
  int row = 5;
  int column = 10;

  Engine engine(row, column);

  SECTION("Initial Direction") {
    engine.PlayerStep();
    REQUIRE(engine.GetDirection() == Direction::kRight);
  }

  SECTION("Up Direction") {
    engine.SetDirection(Direction::kUp);

    REQUIRE(engine.GetDirection() == Direction::kUp);
  }

  SECTION("Down Direction") {
    engine.SetDirection(Direction::kDown);
    REQUIRE(engine.GetDirection() == Direction::kDown);
  }

  SECTION("Left Direction") {
    engine.SetDirection(Direction::kLeft);
    REQUIRE(engine.GetDirection() == Direction::kLeft);
  }

  SECTION("Right Direction") {
    engine.SetDirection(Direction::kRight);
    REQUIRE(engine.GetDirection() == Direction::kRight);
  }

  SECTION("Null Direction") {
    engine.SetDirection(Direction::kNull);
    REQUIRE(engine.GetDirection() == Direction::kNull);
  }
}

TEST_CASE("Change in Location", "[direction][location]") {
  int row = 0;
  int column = 0;

  Engine engine(row, column);

  SECTION("Move Up") {
    REQUIRE(engine.FromDirection(Direction::kUp) == Location{0, -1});
  }

  SECTION("Move Down") {
    REQUIRE(engine.FromDirection(Direction::kDown) == Location{0, +1});
  }

  SECTION("Move Left") {
    REQUIRE(engine.FromDirection(Direction::kLeft) == Location{-1, 0});
  }

  SECTION("Move Right") {
    REQUIRE(engine.FromDirection(Direction::kRight) == Location{+1, 0});
  }

  SECTION("Move Null") {
    REQUIRE(engine.FromDirection(Direction::kNull) == Location{0, 0});
  }
}

TEST_CASE("Player's Location", "[player]") {
  Player player(Location(2, 5));

  SECTION("Player Location") {
    REQUIRE(player.GetLoc() == Location{2,5});
  }

  SECTION("Player Location after a movement") {
    player.SetLoc(Location(1,2));
    REQUIRE(player.GetLoc() == Location{1,2});
  }
}

TEST_CASE("Monster Movement", "[monster]") {
  Map map;
  map.ReadGameScreens();
  map.ReadImageLabels();

  Monster monster;
  monster.SetUpMaps(map);

  REQUIRE_FALSE(monster.IsMonsterMove());

  SECTION("Monster moves") {
    for (int i = 0; i < 21; i++) {
      monster.MoveMonster(Direction::kUp, Location{0, 0},
          3);
    }
    REQUIRE(monster.IsMonsterMove());
    REQUIRE(monster.GetMonsterDirection() == Direction::kUp);
  }
}

TEST_CASE("Player attacks Monster", "[monster]") {
  Map map;
  map.ReadGameScreens();
  map.ReadImageLabels();

  Monster monster;
  monster.SetUpMaps(map);

  SECTION("Monster is not attacked") {
    REQUIRE_FALSE(monster.IsPlayerAttack());
    REQUIRE(monster.GetMonstersKilled() == 0);
  }

  monster.SetIsPlayerAttack(true);
  SECTION("Monster is attacked") {
    REQUIRE(monster.IsPlayerAttack());
  }
}

TEST_CASE("Monster attacks Player", "[location][monster][map]") {
  Map map;
  map.ReadGameScreens();
  map.ReadImageLabels();

  Monster monster;
  monster.SetUpMaps(map);

  SECTION("Player is not attacked") {
    REQUIRE_FALSE(monster.IsMonsterAttackLink(Location(13, 5), 7));
  }

  SECTION("Player is attacked") {
    for (int i = 0; i < 12; i++) {
      monster.IsMonsterAttackLink(Location(12, 6),
          3);
    }
    REQUIRE(monster.IsMonsterAttackLink(Location(12, 6), 3));
  }
}

TEST_CASE("Player Attributes", "[engine][player]") {
  Engine engine(0,0);
  engine.SetPlayerAttributes(3, 20, 5);

  SECTION("Player Health") {
    REQUIRE(engine.GetPlayer().GetCurrentHealth() == 3);
  }

  SECTION("Player's Money amount") {
    REQUIRE(engine.GetPlayer().GetMoneyAmount() == 20);
  }

  SECTION("Monsters killed by player") {

  }
}

TEST_CASE("Player Inventory JSON", "[player]") {
  Player player(Location(5, 10));
  player.AddInfoToMenu();

  nlohmann::json j;

  SECTION("Inventory is empty") { REQUIRE(j.empty()); }

  std::ifstream read_inventory("menu.json");
  read_inventory >> j;

  SECTION("Inventory is not empty") {
    REQUIRE_FALSE(j.empty());
    REQUIRE(j.size() == 5);
  }
}

TEST_CASE("Single Game Screen", "[map][screens]") {
  Map map;

  std::vector<Map> single_screen;
  single_screen.push_back(sample_map);
  map.SetGameScreens(single_screen);

  REQUIRE(map.GetScreen().size() == 1);
}

TEST_CASE("Screen Labels and Screens", "[map][screens][labels]") {
  Map map;
  map.ReadGameScreens();
  map.ReadImageLabels();

  std::vector<Map> game_screens = map.GetScreen();

  SECTION("Number of Labels and screens") {
    REQUIRE(game_screens.size() == 26);
  }

  SECTION("Map Label") {
    std::string map_label = "screen-H8.png";
    REQUIRE(map.GetMapLabels() == map_label);
    REQUIRE(map.GetNewScreenNum() == 0);
  }

  SECTION("Screen Number") {
    int screen_num = map.GetCurrScreenNum(sample_map);
    REQUIRE(screen_num == 32766);
  }
}

TEST_CASE("Check for Screen Change", "[screen]") {
  Map map;
  map.ReadGameScreens();
  map.ReadImageLabels();

  int row = 0;
  int column = 0;

  Engine engine(row, column);
  Location location = map.GetPlayerNewLoc(sample_map, engine);

  SECTION("No Screen Change has taken place") {
    REQUIRE_FALSE(map.IsScreenChange());
  }

  SECTION("Initial player Location - before screen change") {
    REQUIRE(location == Location(10,5));
  }

  engine.Reset(Location(0,4));
  Location new_loc = map.GetPlayerNewLoc(sample_map, engine);
  SECTION("Screen Change has taken place") {
    REQUIRE(map.IsScreenChange());
  }

  SECTION("New player Location - after screen change") {
    REQUIRE(new_loc == Location(1,4));
  }

  SECTION("Changed Map Screen Number") {
    // Screen change when exited from 'h'
    REQUIRE(map.GetTransitionScreenNum(5, 'h') == 3);

    // Screen change when exited from 'e'
    REQUIRE(map.GetTransitionScreenNum(4, 'e') == 5);
  }

  SECTION("Changed Cave Screen Number") {
    REQUIRE(map.GetTransitionScreenNum(7, '!') == 8);
  }

  SECTION("Is Sword Taken") {
    REQUIRE_FALSE(map.IsSwordTaken());
  }
}
