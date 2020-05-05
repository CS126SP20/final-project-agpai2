//
// Created by Aniruddha Pai on 4/17/20.
//

#include <zelda/engine.h>
#include <zelda/location.h>
#include <zelda/player.h>

namespace zelda {

Engine::Engine(int width, int height)
    : width_{width},
      height_{height},
      direction_{Direction::kRight},
      last_direction_{Direction::kUp},
      player_{Location(2 * kLocConstant, kLocConstant)} {
}

void Engine::SetDirection(const zelda::Direction direction) {
  direction_ = direction;
}

Direction Engine::GetDirection() { return direction_; }

Player Engine::GetPlayer() const { return player_; }

void Engine::SetPlayerAttributes(int health, int money, int monsters_killed) {
  player_.SetCurrentHealth(health);
  player_.SetMoneyAmount(money);
  player_.SetMonstersKilled(monsters_killed);
}

// Converts a direction into a delta location.
Location Engine::FromDirection(const Direction direction) {
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

void Engine::PlayerStep() {
  Location next_loc = FromDirection(direction_);
  Location new_player_loc =
      (player_.GetLoc() + next_loc) % Location(height_, width_);

  player_.SetLoc(new_player_loc);

  last_direction_ = direction_;
}

void Engine::Reset(Location location) {
  player_.SetLoc(location);
}

} // namespace zelda