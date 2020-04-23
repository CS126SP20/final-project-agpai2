//
// Created by Aniruddha Pai on 4/17/20.
//

#include <mylibrary/engine.h>
#include <mylibrary/location.h>
#include <mylibrary/player.h>

namespace mylibrary {

// Converts a direction into a delta location.
Location FromDirection(const Direction direction) {
  switch (direction) {
    case Direction::kUp:
      return {0, -1};
    case Direction::kDown:
      return {0, +1};
    case Direction::kLeft:
      return {-1, 0};
    case Direction::kRight:
      return {+1, 0};
    case Direction::kNull:
      return {0,0};
  }
}

Player Engine::GetPlayer() const { return player_; }

void Engine::Reset() {
  Location location(kLocConstant, 2 * kLocConstant);
  player_.SetLoc(location);
}

Engine::Engine(int width, int height)
    : width_{width},
      height_{height},
      direction_{Direction::kRight},
      last_direction_{Direction::kUp},
      player_{Location(0,0)} {
  Reset();
}

void Engine::SetDirection(const mylibrary::Direction direction) {
  direction_ = direction;
}

void Engine::Step() {
  Location next_loc = FromDirection(direction_);
  Location new_player_loc =
      (player_.GetLoc() + next_loc) % Location(height_, width_);

  player_.SetLoc(new_player_loc);

  last_direction_ = direction_;
}

Direction Engine::GetDirection() { return direction_; }

}