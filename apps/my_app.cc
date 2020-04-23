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

Zelda::Zelda()
    : engine_{kRowTiles, kColTiles},
      size_{kRowTiles} {}

void Zelda::setup() {
  cinder::gl::disableDepthWrite();
  cinder::gl::disableDepthRead();

  ReadMapsFromFile();
  PlayBackgroundTheme();
}

void Zelda::update() {
  Location location = engine_.GetPlayer().GetLoc();

  // The current row contains player's column coordinate and
  // the current column contains to player's row coordinate

  // This is to account for the switch in coordinates axes
  int curr_row = location.Col();
  int curr_col = location.Row();


  for (int i = 0; i < game_maps_.size(); i++) {
    is_move_right_ = game_maps_[i].coordinates_[curr_row][curr_col + 1] != '1';

    is_move_down_ = game_maps_[i].coordinates_[curr_row + 1][curr_col] != '1';

    is_move_left_ = game_maps_[i].coordinates_[curr_row][curr_col - 1] != '1';

    is_move_up_ = game_maps_[i].coordinates_[curr_row - 1][curr_col] != '1';
  }
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
      player_move_state = static_cast<int>(Direction::kUp);
      DrawPlayer();
      engine_.Step();
      break;
    }
    case KeyEvent::KEY_DOWN:
    case KeyEvent::KEY_s: {
      CheckForDirection(event);
      player_move_state = static_cast<int>(Direction::kDown);
      DrawPlayer();
      engine_.Step();
      break;
    }
    case KeyEvent::KEY_LEFT:
    case KeyEvent::KEY_a: {
      CheckForDirection(event);
      player_move_state = static_cast<int>(Direction::kLeft);
      DrawPlayer();
      engine_.Step();
      break;
    }
    case KeyEvent::KEY_RIGHT:
    case KeyEvent::KEY_d: {
      CheckForDirection(event);
      player_move_state = static_cast<int>(Direction::kRight);
      DrawPlayer();
      engine_.Step();
      break;
    }
  }
}

void Zelda::CheckForDirection(const cinder::app::KeyEvent& event) {

  // Checks if the player can move up
  if (is_move_up_ &&
      ((event.getCode() == KeyEvent::KEY_UP) ||
      (event.getCode() == KeyEvent::KEY_w))) {
    engine_.SetDirection(Direction::kUp);
    return;
  } else {
    engine_.SetDirection(Direction::kNull);
  }

  // Checks if the player can move down
  if (is_move_down_ &&
      ((event.getCode() == KeyEvent::KEY_DOWN) ||
      (event.getCode() == KeyEvent::KEY_s))) {
    engine_.SetDirection(Direction::kDown);
    return;
  } else {
    engine_.SetDirection(Direction::kNull);
  }

  // Checks if the player can move left
  if (is_move_left_ &&
      ((event.getCode() == KeyEvent::KEY_LEFT )||
      (event.getCode() == KeyEvent::KEY_a))) {
    engine_.SetDirection(Direction::kLeft);
    return;
  } else {
    engine_.SetDirection(Direction::kNull);
  }

  // Checks if the player can move right
  if (is_move_right_ &&
      ((event.getCode() == KeyEvent::KEY_RIGHT) ||
      (event.getCode() == KeyEvent::KEY_d))) {
    engine_.SetDirection(Direction::kRight);
    return;
  } else {
    engine_.SetDirection(Direction::kNull);
  }
}

void Zelda::PlayBackgroundTheme() {
  auto source_file = cinder::audio::load
      (cinder::app::loadAsset("zelda.mp3"));
  background_audio_file = cinder::audio::Voice::create(source_file);
  background_audio_file->start();
}

void Zelda::DrawPlayer() {
  const Location loc = engine_.GetPlayer().GetLoc();
  cinder::fs::path path;

  // The sequence of 'if' conditions changes image of link
  // based on the direction Link is planning to move
  if (player_move_state == static_cast<int>(Direction::kDown)) {
    path = cinder::fs::path("link.png");
  } else if (player_move_state == static_cast<int>(Direction::kUp)) {
    path = cinder::fs::path("link-back.png");
  } else if (player_move_state == static_cast<int>(Direction::kLeft)) {
    path = cinder::fs::path("link-left.png");
  } else if (player_move_state == static_cast<int>(Direction::kRight)) {
    path = cinder::fs::path("link-right.png");

  }

  cinder::gl::Texture2dRef texture = cinder::gl::Texture2d::create(
      loadImage(loadAsset(path)));

  cinder::gl::draw(texture, Rectf(kTileSize * loc.Row(),
                                  kTileSize * loc.Col(),
                                  kTileSize * loc.Row() + kTileSize,
                                  kTileSize * loc.Col() + kTileSize));
}

void Zelda::DrawBackground() {
  cinder::fs::path path = cinder::fs::path("zelda-screen1.png");
  cinder::gl::Texture2dRef texture = cinder::gl::Texture2d::create(
      loadImage(loadAsset(path)));

  cinder::gl::draw(texture, getWindowBounds());
}

void Zelda::ReadMapsFromFile() {
  int map_line_count = 0;

  std::string maps_file =
      "/Users/aniruddhapai/Downloads/cinder_0.9.2_mac/finalproject/final-project-agpai2/assets/zeldamaps.txt";
  std::ifstream file(maps_file);

  while (!file.eof()) {
    std::string map_line;
    getline(file, map_line);
    SetUpMap(map_line);
    map_line_count++;

    // This to account for the fact that the game screen
    // has 13 rows.
    // So, game_maps_ takes in a new game screen after 13 counts
    if (map_line_count == kRowTiles) {
      Map game_screen = Map(map_);
      game_maps_.push_back(game_screen);
      map_line_count = 0;

      map_.clear();
    }
  }
}

void Zelda::SetUpMap(std::string map_line) {
  std::vector<char> map_line_char;

  for (int i = 0; i < kColTiles; i++) {
    if (map_line.at(i) == '1') {
      map_line_char.push_back('1');
    } else if (map_line.at(i) == '0') {
      map_line_char.push_back('0');
    }
  }

  map_.push_back(map_line_char);
}

}  // namespace myapp
