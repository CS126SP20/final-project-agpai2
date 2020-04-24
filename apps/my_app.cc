// Copyright (c) 2020 [Your Name]. All rights reserved.

#include "my_app.h"

#include <cinder/app/App.h>
#include <cinder/gl/gl.h>
#include <cinder/gl/Texture.h>
#include <cinder/gl/draw.h>

namespace myapp {

using cinder::app::KeyEvent;
using cinder::Rectf;

using mylibrary::Direction;
using mylibrary::Location;
using mylibrary::Map;

int map_num = 0;

int front_move_count = 0;
int left_move_count = 0;
int right_move_count = 0;
int back_move_count = 0;

cinder::fs::path move_path;

Zelda::Zelda()
    : engine_{kRowTiles, kColTiles},
      size_{kRowTiles} {}

void Zelda::setup() {
  cinder::gl::disableDepthWrite();
  cinder::gl::disableDepthRead();

  curr_map_ = "zelda-screen1.png";
  mapper_.ReadImageLabels();
  mapper_.ReadGameScreens();
  PlayBackgroundTheme();
}

void Zelda::update() {
  Location location = engine_.GetPlayer().GetLoc();

  Location new_player_loc = mapper_.GetPlayerNewLoc(
      mapper_.GetScreen()[map_num],engine_);

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

  cinder::gl::clear();
  cinder::gl::color(1,1,1);

  DrawBackground();
  DrawPlayer();
}

void Zelda::keyDown(KeyEvent event) {
  switch (event.getCode()) {
    case KeyEvent::KEY_UP:
    case KeyEvent::KEY_w: {
      CheckForDirection(event);
      player_move_state_ = static_cast<int>(Direction::kUp);
      back_move_count++;
      DrawPlayer();
      engine_.Step();
      break;
    }
    case KeyEvent::KEY_DOWN:
    case KeyEvent::KEY_s: {
      CheckForDirection(event);
      player_move_state_ = static_cast<int>(Direction::kDown);
      front_move_count++;
      DrawPlayer();
      engine_.Step();
      break;
    }
    case KeyEvent::KEY_LEFT:
    case KeyEvent::KEY_a: {
      CheckForDirection(event);
      player_move_state_ = static_cast<int>(Direction::kLeft);
      left_move_count++;
      DrawPlayer();
      engine_.Step();
      break;
    }
    case KeyEvent::KEY_RIGHT:
    case KeyEvent::KEY_d: {
      CheckForDirection(event);
      player_move_state_ = static_cast<int>(Direction::kRight);
      right_move_count++;
      DrawPlayer();
      engine_.Step();
      break;
    }
  }
}

void Zelda::CheckForDirection(const cinder::app::KeyEvent& event) {

  if (is_move_up_ &&
      (event.getCode() == KeyEvent::KEY_UP ||
      event.getCode() == KeyEvent::KEY_w)) {
    engine_.SetDirection(Direction::kUp);
    return;
  } else {
    engine_.SetDirection(Direction::kNull);
  }

  if (is_move_down_ &&
      (event.getCode() == KeyEvent::KEY_DOWN ||
      event.getCode() == KeyEvent::KEY_s)) {
    engine_.SetDirection(Direction::kDown);
    return;
  } else {
    engine_.SetDirection(Direction::kNull);
  }

  if (is_move_left_ &&
      (event.getCode() == KeyEvent::KEY_LEFT ||
      event.getCode() == KeyEvent::KEY_a)) {
    engine_.SetDirection(Direction::kLeft);
    return;
  } else {
    engine_.SetDirection(Direction::kNull);
  }

  if (is_move_right_ &&
      (event.getCode() == KeyEvent::KEY_RIGHT ||
      event.getCode() == KeyEvent::KEY_d)) {
    engine_.SetDirection(Direction::kRight);
    return;
  } else {
    engine_.SetDirection(Direction::kNull);
  }
}

void Zelda::PlayBackgroundTheme() {
  auto audio_path = "zelda.mp3";

  auto source_file = cinder::audio::load
      (cinder::app::loadAsset(audio_path));
  background_audio_file_ = cinder::audio::Voice::create(source_file);
  background_audio_file_->start();

}

void Zelda::DrawPlayer() {
  const Location loc = engine_.GetPlayer().GetLoc();

  if (player_move_state_ == static_cast<int>(Direction::kDown)) {
    if (front_move_count % 2 == 0) {
      move_path = cinder::fs::path("link-front-1.png");
    } else {
      move_path = cinder::fs::path("link-front-2.png");
    }
  } else if (player_move_state_ == static_cast<int>(Direction::kUp)) {
    if (back_move_count % 2 == 0) {
      move_path = cinder::fs::path("link-back-1.png");
    } else {
      move_path = cinder::fs::path("link-back-2.png");
    }
  } else if (player_move_state_ == static_cast<int>(Direction::kLeft)) {
    if (left_move_count % 2 == 0) {
      move_path = cinder::fs::path("link-left-1.png");
    } else {
      move_path = cinder::fs::path("link-left-2.png");
    }
  } else if (player_move_state_ == static_cast<int>(Direction::kRight)) {
    if (right_move_count % 2 == 0) {
      move_path = cinder::fs::path("link-right-1.png");
    } else {
      move_path = cinder::fs::path("link-right-2.png");
    }
  }

  if (mapper_.GetScreen()[map_num].coordinates_[loc.Col()][loc.Row()] == 't') {
    move_path = cinder::fs::path("link-sword.png");
  }

  cinder::gl::Texture2dRef texture = cinder::gl::Texture2d::create(
      loadImage(loadAsset(move_path)));

  cinder::gl::draw(texture, Rectf(kTileSize * loc.Row(),
                                  kTileSize * loc.Col(),
                                  kTileSize * loc.Row() + kTileSize,
                                  kTileSize * loc.Col() + kTileSize));
}

void Zelda::DrawBackground() {
  cinder::gl::Texture2dRef texture = cinder::gl::Texture2d::create(
      loadImage(loadAsset(curr_map_)));

  cinder::gl::draw(texture, getWindowBounds());
}

void Zelda::ResetPosition(Location location) {
  if (mapper_.IsScreenChange()) {
    engine_.Reset(location);
  }
}

}  // namespace myapp
