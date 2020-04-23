//
// Created by Aniruddha Pai on 4/17/20.
//

#ifndef FINALPROJECT_ENGINE_H
#define FINALPROJECT_ENGINE_H

#include "direction.h"
#include "player.h"

namespace mylibrary {

constexpr int kLocConstant = 5;

class Engine {
 public:
  Engine(int width, int height);

  // Changes the direction of the player for the next step.
  void SetDirection(Direction);

  // Executes a time step: moves the player.
  void Step();

  // Start the game over.
  void Reset();

  // Resets the players location after a screen transition
  void Reset(Location location);

  // Gets the player
  Player GetPlayer() const;

  //Gets the direction
  Direction GetDirection();

 private:
  const int width_;
  const int height_;
  Direction direction_;
  Direction last_direction_;

  Player player_;
};

}

#endif  // FINALPROJECT_ENGINE_H
