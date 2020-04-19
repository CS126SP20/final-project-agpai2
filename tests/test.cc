// Copyright (c) 2020 CS126SP20. All rights reserved.

#define CATCH_CONFIG_MAIN

#include <catch2/catch.hpp>
#include <cinder/Rand.h>

#include <mylibrary/example.h>

#include <mylibrary/location.h>

using mylibrary::Location;

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
}
