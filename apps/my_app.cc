// Copyright (c) 2020 [Your Name]. All rights reserved.

#include "my_app.h"

#include <cinder/app/App.h>

#include <cinder/audio/Voice.h>
#include <cinder/gl/gl.h>

#include <cinder/gl/Texture.h>
#include <cinder/gl/draw.h>

namespace myapp {

using cinder::app::KeyEvent;
using cinder::Rectf;

using mylibrary::Direction;
using mylibrary::Location;
using mylibrary::Map;

cinder::audio::VoiceRef background_audio_file;
int player_move_state = 0;

Zelda::Zelda()
    : engine_{kRowTiles, kColTiles},
      size_{kRowTiles} {}

void Zelda::setup() {
  cinder::gl::disableDepthWrite();
  cinder::gl::disableDepthRead();

  PlayBackgroundTheme();
}

void Zelda::update() {}

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
    case KeyEvent::KEY_k:
    case KeyEvent::KEY_w: {
      engine_.SetDirection(Direction::kLeft);
      player_move_state = 1;
      DrawPlayer();
      engine_.Step();
      break;
    }
    case KeyEvent::KEY_DOWN:
    case KeyEvent::KEY_j:
    case KeyEvent::KEY_s: {
      engine_.SetDirection(Direction::kRight);
      player_move_state = 0;
      DrawPlayer();
      engine_.Step();
      break;
    }
    case KeyEvent::KEY_LEFT:
    case KeyEvent::KEY_h:
    case KeyEvent::KEY_a: {
      engine_.SetDirection(Direction::kUp);
      player_move_state = 2;
      DrawPlayer();
      engine_.Step();
      break;
    }
    case KeyEvent::KEY_RIGHT:
    case KeyEvent::KEY_l:
    case KeyEvent::KEY_d: {
      engine_.SetDirection(Direction::kDown);
      player_move_state = 3;
      DrawPlayer();
      engine_.Step();
      break;
    }
  }
}

void Zelda::CheckForDirection(const cinder::app::KeyEvent& event) {}

void Zelda::PlayBackgroundTheme() {
  auto source_file = cinder::audio::load
      (cinder::app::loadAsset("zelda.mp3"));
  background_audio_file = cinder::audio::Voice::create(source_file);
  background_audio_file->start();
}

void Zelda::DrawPlayer() {
  const Location loc = engine_.GetPlayer().GetLoc();
  cinder::fs::path path;

  if (player_move_state == 0) {
    path = cinder::fs::path("link.png");
  } else if (player_move_state == 1) {
    path = cinder::fs::path("link-back.png");
  } else if (player_move_state == 2) {
    path = cinder::fs::path("link-left.png");
  } else if (player_move_state == 3) {
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

  std::string maps_file
      = "/Users/aniruddhapai/Downloads/cinder_0.9.2_mac/finalproject/zelda-trials/assets/zeldamaps.txt";
  std::ifstream file(maps_file);

  while (!file.eof()) {
    std::string map_line;
    getline(file, map_line);
    SetUpMap(map_line);
    map_line_count++;

    if (map_line_count == 13) {
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
