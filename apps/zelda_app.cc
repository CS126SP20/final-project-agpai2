// Copyright (c) 2020 [Your Name]. All rights reserved.

#include "zelda_app.h"

#include <cinder/app/App.h>
#include <cinder/gl/Texture.h>
#include <cinder/gl/draw.h>
#include <cinder/gl/gl.h>

namespace zeldaapp {

using cinder::app::KeyEvent;
using cinder::Rectf;

using zelda::Direction;
using zelda::Location;
using zelda::Map;

int map_num = 0;

int front_move_count = 0;
int left_move_count = 0;
int right_move_count = 0;
int back_move_count = 0;

// This count is kept to slow down the monster
int slow_monster_count = 0;

// This count is kept to for a time delay to show Link attack
int attack_count = 0;

cinder::fs::path move_path;
cinder::fs::path attack_path;

Zelda::Zelda()
    : player_engine_{kRowTiles, kColTiles},
      monster_{},
      is_game_paused_{false},
      size_{kRowTiles} {}

void Zelda::setup() {
  cinder::gl::disableDepthWrite();
  cinder::gl::disableDepthRead();

  curr_map_ = "screen-H8.png";
  mapper_.ReadImageLabels();
  mapper_.ReadGameScreens();

  monster_.SetUpMaps(mapper_);

  PlayBackgroundTheme();
  PlayTreasureSound();
}

void Zelda::update() {
  if (is_game_paused_) { return; }

  Location location = player_engine_.GetPlayer().GetLoc();

  slow_monster_count++;
  if (slow_monster_count % kColTiles == 0) {
    mapper_.SetGameScreens(monster_.MoveMonster(player_move_state_,
        location ,map_num));
    slow_monster_count = 0;
  }

  Location new_player_loc = mapper_.GetPlayerNewLoc(
      mapper_.GetScreen()[map_num],player_engine_);

  curr_map_ = mapper_.GetMapLabels();

  map_num = mapper_.GetNewScreenNum();

  int curr_row = location.Col();
  int curr_col = location.Row();

  // Resets Link's position based on the screen change
  ResetPosition(new_player_loc);

  // This is to check if it is possible to move in any given direction
  is_move_right_ =
      mapper_.GetScreen()[map_num].coordinates_[curr_row][curr_col + 1] != '1';

  is_move_down_ =
      mapper_.GetScreen()[map_num].coordinates_[curr_row + 1][curr_col] != '1';

  is_move_left_ =
      mapper_.GetScreen()[map_num].coordinates_[curr_row][curr_col - 1] != '1';

  is_move_up_ =
      mapper_.GetScreen()[map_num].coordinates_[curr_row - 1][curr_col] != '1';
}

void Zelda::draw() {
  cinder::gl::enableAlphaBlending();

  if (is_game_paused_) {
    DisplayMenu();
    return;
  }

  cinder::gl::clear();
  cinder::gl::color(1,1,1);

  DrawBackground();

  if (!is_attack_) {
    DrawPlayer();
  } else {
    DrawAttackLink();
  }

  DrawMonster();
}

void Zelda::keyDown(KeyEvent event) {
  switch (event.getCode()) {
    case KeyEvent::KEY_UP:
    case KeyEvent::KEY_w: {
      if (!is_game_paused_) {
        CheckForDirection(event);
        player_move_state_ = Direction::kUp;
        back_move_count++;
        DrawPlayer();
        player_engine_.PlayerStep();
      }
      break;
    }
    case KeyEvent::KEY_DOWN:
    case KeyEvent::KEY_s: {
      if (!is_game_paused_) {
        CheckForDirection(event);
        player_move_state_ = Direction::kDown;
        front_move_count++;
        DrawPlayer();
        player_engine_.PlayerStep();
      }
      break;
    }
    case KeyEvent::KEY_LEFT:
    case KeyEvent::KEY_a: {
      if (!is_game_paused_) {
        CheckForDirection(event);
        player_move_state_ = Direction::kLeft;
        left_move_count++;
        DrawPlayer();
        player_engine_.PlayerStep();
      }
      break;
    }
    case KeyEvent::KEY_RIGHT:
    case KeyEvent::KEY_d: {
      if (!is_game_paused_) {
        CheckForDirection(event);
        player_move_state_ = Direction::kRight;
        right_move_count++;
        DrawPlayer();
        player_engine_.PlayerStep();
      }
      break;
    }
    case KeyEvent::KEY_p: {
      is_game_paused_ = !is_game_paused_;

      if (is_game_paused_) {
        player_engine_.GetPlayer().AddInfoToMenu();
        player_engine_.GetPlayer().ViewMenu();
        last_pause_time_ = std::chrono::system_clock::now();
      } else {
        last_intact_time_ += std::chrono::system_clock::now() - last_pause_time_;
      }
      break;
    }
    case KeyEvent::KEY_SPACE: {
      if (mapper_.IsSwordTaken()) {
        is_attack_ = true;
      }
    }
  }
}

void Zelda::CheckForDirection(const cinder::app::KeyEvent& event) {

  if (is_move_up_ &&
      (event.getCode() == KeyEvent::KEY_UP ||
      event.getCode() == KeyEvent::KEY_w)) {
    player_engine_.SetDirection(Direction::kUp);
    return;
  } else {
    player_engine_.SetDirection(Direction::kNull);
  }

  if (is_move_down_ &&
      (event.getCode() == KeyEvent::KEY_DOWN ||
      event.getCode() == KeyEvent::KEY_s)) {
    player_engine_.SetDirection(Direction::kDown);
    return;
  } else {
    player_engine_.SetDirection(Direction::kNull);
  }

  if (is_move_left_ &&
      (event.getCode() == KeyEvent::KEY_LEFT ||
      event.getCode() == KeyEvent::KEY_a)) {
    player_engine_.SetDirection(Direction::kLeft);
    return;
  } else {
    player_engine_.SetDirection(Direction::kNull);
  }

  if (is_move_right_ &&
      (event.getCode() == KeyEvent::KEY_RIGHT ||
      event.getCode() == KeyEvent::KEY_d)) {
    player_engine_.SetDirection(Direction::kRight);
    return;
  } else {
    player_engine_.SetDirection(Direction::kNull);
  }
}

void Zelda::PlayBackgroundTheme() {
  auto audio_path = "zelda.mp3";

  auto source_file = cinder::audio::load
      (cinder::app::loadAsset(audio_path));
  background_audio_file_ = cinder::audio::Voice::create(source_file);
  background_audio_file_->start();

}

void Zelda::PlayTreasureSound() {
  auto audio_path = "treasure.mp3";

  auto source_file = cinder::audio::load
      (cinder::app::loadAsset(audio_path));
  treasure_audio_file_ = cinder::audio::Voice::create(source_file);
}

void Zelda::DrawPlayer() {
  const Location loc = player_engine_.GetPlayer().GetLoc();

  if (player_move_state_ == Direction::kDown) {
    if (front_move_count % 2 == 0) {
      move_path = cinder::fs::path("link-front-1.png");
    } else {
      move_path = cinder::fs::path("link-front-2.png");
    }
  } else if (player_move_state_ == Direction::kUp) {
    if (back_move_count % 2 == 0) {
      move_path = cinder::fs::path("link-back-1.png");
    } else {
      move_path = cinder::fs::path("link-back-2.png");
    }
  } else if (player_move_state_ == Direction::kLeft) {
    if (left_move_count % 2 == 0) {
      move_path = cinder::fs::path("link-left-1.png");
    } else {
      move_path = cinder::fs::path("link-left-2.png");
    }
  } else if (player_move_state_ == Direction::kRight) {
    if (right_move_count % 2 == 0) {
      move_path = cinder::fs::path("link-right-1.png");
    } else {
      move_path = cinder::fs::path("link-right-2.png");
    }
  }

  if (mapper_.GetScreen()[map_num].coordinates_[loc.Col()][loc.Row()] == 't') {
    move_path = cinder::fs::path("link-sword.png");
    background_audio_file_->pause();
    treasure_audio_file_->start();
  }

  if (!treasure_audio_file_->isPlaying()) {
    background_audio_file_->start();
  }

  cinder::gl::Texture2dRef texture = cinder::gl::Texture2d::create(
      loadImage(loadAsset(move_path)));

  cinder::gl::draw(texture, Rectf((kCharacterSize * loc.Row() *
  getWindowWidth()/kFullScreenWidth),
      (kCharacterSize * loc.Col() * getWindowHeight()/kFullScreenHeight),
      (kCharacterSize * loc.Row() * getWindowWidth()/kFullScreenWidth) +
                                      kCharacterSize,
      (kCharacterSize * loc.Col() * getWindowHeight()/kFullScreenHeight) +
                                      kCharacterSize));
}

void Zelda::DrawMonster() {
  cinder::fs::path monster_path;

  monster_path = cinder::fs::path("octorok-right-1.png");
  if (mapper_.direction == Direction::kUp) {
    monster_path = cinder::fs::path("octorok-up-1.png");
  } else if (mapper_.direction == Direction::kDown) {
    monster_path = cinder::fs::path("octorok-down-1.png");
  } else if (mapper_.direction == Direction::kLeft) {
    monster_path = cinder::fs::path("octorok-left-1.png");
  } else if (mapper_.direction == Direction::kRight) {
    monster_path = cinder::fs::path("octorok-right-1.png");
  }
  //monster_path = cinder::fs::path("octorok-right-1.png");
  cinder::gl::Texture2dRef texture = cinder::gl::Texture2d::create(
      loadImage(loadAsset(monster_path)));

  for (int i = 0; i < kRowTiles; i++) {
    for (int j = 0; j < kColTiles; j++) {
      if (mapper_.GetScreen()[map_num].coordinates_[i][j] == 'M') {
        cinder::gl::draw(texture, Rectf((kCharacterSize * j *
        getWindowWidth()/kFullScreenWidth),
                                        (kCharacterSize * i *
                                        getWindowHeight()/kFullScreenHeight),
                                        (kCharacterSize * j *
                                        getWindowWidth()/kFullScreenWidth) +
                                        kCharacterSize,
                                        (kCharacterSize * i *
                                        getWindowHeight()/kFullScreenHeight) +
                                        kCharacterSize));
      }
    }
  }
}

void Zelda::DrawAttackLink() {
  const Location loc = player_engine_.GetPlayer().GetLoc();

  if (player_move_state_ == Direction::kDown) {
    attack_path = cinder::fs::path("link-attack-front.png");
  } else if (player_move_state_ == Direction::kUp) {
    attack_path = cinder::fs::path("link-attack-back.png");
  } else if (player_move_state_ == Direction::kLeft) {
    attack_path = cinder::fs::path("link-attack-left.png");
  } else if (player_move_state_ == Direction::kRight) {
    attack_path = cinder::fs::path("link-attack-right.png");
  }

  cinder::gl::Texture2dRef texture = cinder::gl::Texture2d::create(
      loadImage(loadAsset(attack_path)));

  cinder::gl::draw(texture, Rectf((kAttackLinkSize *
  (loc.Row()/kRatio) * getWindowWidth()/kFullScreenWidth),
                                  (kAttackLinkSize * (loc.Col()/kRatio) *
                                  getWindowHeight()/kFullScreenHeight),
                                  (kAttackLinkSize * (loc.Row()/kRatio) *
                                  getWindowWidth()/kFullScreenWidth) +
                                  kAttackLinkSize,
                                  (kAttackLinkSize * (loc.Col()/kRatio) *
                                  getWindowHeight()/kFullScreenHeight) +
                                  kAttackLinkSize));

  attack_count++;

  if (attack_count % 5 == 0) {
    is_attack_ = false;
    attack_count = 0;
  }
}

void Zelda::DrawBackground() {
  cinder::gl::Texture2dRef texture = cinder::gl::Texture2d::create(
      loadImage(loadAsset(curr_map_)));

  cinder::gl::draw(texture, getWindowBounds());
}

void Zelda::DisplayMenu() {
  cinder::fs::path menu_path = cinder::fs::path("inventory.png");
  cinder::gl::Texture2dRef texture = cinder::gl::Texture2d::create(
      loadImage(loadAsset(menu_path)));


  cinder::gl::draw(texture, getWindowBounds());
}

void Zelda::ResetPosition(Location location) {
  if (mapper_.IsScreenChange()) {
    player_engine_.Reset(location);
  }
}

}  // namespace zeldaapp
