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

cinder::audio::VoiceRef background_audio_file;
int player_move_state = 0;

MyApp::MyApp()
    : engine_{kNumTiles, kNumTiles},
      size_{kNumTiles} {}

void MyApp::setup() {
  PlayBackgroundTheme();
}

void MyApp::update() {}

void MyApp::draw() {}

void MyApp::keyDown(KeyEvent event) {}

void MyApp::PlayBackgroundTheme() {
  auto source_file = cinder::audio::load
      (cinder::app::loadAsset("zelda.mp3"));
  background_audio_file = cinder::audio::Voice::create(source_file);
  background_audio_file->start();
}
void MyApp::DrawPlayer() {}

}  // namespace myapp
