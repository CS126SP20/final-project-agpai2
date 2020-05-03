//
// Created by Aniruddha Pai on 4/17/20.
//

#ifndef FINALPROJECT_ENGINE_H
#define FINALPROJECT_ENGINE_H

#include "direction.h"
#include "player.h"

namespace zelda {

constexpr int kLocConstant = 5;

class Engine {
 public:
  Engine(int width, int height);

  // Changes the direction of the player for the next step.
  void SetDirection(Direction);

  // Executes a time step: moves the player.
  void PlayerStep();

  // Resets the players location after a screen transition
  void Reset(Location location);

  // Gets the player
  Player GetPlayer() const;

  //Gets the direction
  Direction GetDirection();

  // Changes the coordinates after change in direction
  Location FromDirection(Direction direction);

  // Sets the current health of the player
  void SetCurrentPlayerHealth(int current_health);

 private:
  const int width_;
  const int height_;
  Direction direction_;
  Direction last_direction_;

  Player player_;
};

} // namespace zelda

#endif  // FINALPROJECT_ENGINE_H
