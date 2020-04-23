// Copyright (c) 2020 CS126SP20. All rights reserved.

#ifndef FINALPROJECT_APPS_MYAPP_H_
#define FINALPROJECT_APPS_MYAPP_H_

#include <cinder/app/App.h>
#include <cinder/app/KeyEvent.h>
#include <cinder/audio/Voice.h>
#include <mylibrary/engine.h>
#include <mylibrary/location.h>
#include <mylibrary/map.h>

namespace myapp {

const int kTileSize = 70;
const int kRowTiles = 13;
const int kColTiles = 21;

class Zelda : public cinder::app::App {
 public:
  Zelda();
  void setup() override;
  void update() override;
  void draw() override;
  void keyDown(cinder::app::KeyEvent) override;

 private:
  void PlayBackgroundTheme();
  void PlayTreasureSound();
  void DrawPlayer();
  void DrawBackground();
  void CheckForDirection(const cinder::app::KeyEvent& event);


 private:
  mylibrary::Engine engine_;
  mylibrary::Map mapper_;
  const size_t size_;

  // The current map the player is on
  std::string curr_map_;

  // The bool values are to check for the possible directions
  bool is_move_right_ = true;
  bool is_move_left_ = true;
  bool is_move_up_ = true;
  bool is_move_down_ = true;

  int player_move_state_ = 0;

  cinder::audio::VoiceRef background_audio_file_;
  void ResetPosition(mylibrary::Location location);
};

}  // namespace myapp

#endif  // FINALPROJECT_APPS_MYAPP_H_
