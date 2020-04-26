// Copyright (c) 2020 CS126SP20. All rights reserved.

#define CATCH_CONFIG_MAIN

#include <cinder/Rand.h>

#include <catch2/catch.hpp>

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

std::vector<std::vector<char>> sample_screen = {{ '1','1','1','0','0','1','0','0','1','0','0','0','1','0','1','0','0','1','0','1','1'},
                                                { '1','1','1','0','0','1','0','0','1','0','0','0','1','0','1','0','0','1','0','1','1'},
                                                { '1','1','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','1','1'},
                                                { '1','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','1','1'},
                                                { 'h','0','0','0','0','1','0','0','0','0','0','0','1','0','0','0','0','1','0','1','1'},
                                                { 'h','0','1','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','j'},
                                                { 'h','0','0','0','0','1','0','1','1','0','0','1','1','0','1','0','0','1','0','0','j'},
                                                { 'h','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','j'},
                                                { 'h','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','j'},
                                                { '1','0','0','0','0','1','0','0','0','0','0','0','1','0','0','0','0','1','0','1','1'},
                                                { '1','1','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','1','1'},
                                                { '1','1','1','1','0','1','0','1','1','0','0','1','1','0','1','0','0','1','0','1','1'},
                                                { '1','1','1','1','e','1','e','e','1','e','e','e','1','e','1','e','e','1','e','1','1' }};

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
}

TEST_CASE("Player's and Monster's Location", "[player][monster]") {
  Player player(Location(2, 5));
  Monster monster(Location(7,2));

  SECTION("Player Location") {
    REQUIRE(player.GetLoc() == Location{2,5});
  }

  SECTION("Player Location after a movement") {
    player.SetLoc(Location(1,2));
    REQUIRE(player.GetLoc() == Location{1,2});
  }

  SECTION("Monster Location") {
    REQUIRE(monster.GetLoc() == Location{7,2});
  }

  SECTION("Monster Location after movement") {
    monster.SetLoc(Location(6,9));
    REQUIRE(monster.GetLoc() == Location{6,9});
  }
}
