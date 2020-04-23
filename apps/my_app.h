// Copyright (c) 2020 CS126SP20. All rights reserved.

#ifndef FINALPROJECT_APPS_MYAPP_H_
#define FINALPROJECT_APPS_MYAPP_H_

#include <cinder/app/App.h>
#include <cinder/app/KeyEvent.h>
#include <mylibrary/engine.h>
#include <mylibrary/map.h>
#include <cinder/audio/Voice.h>

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
  void DrawPlayer();
  void DrawBackground();
  void ReadMapsFromFile();
  void CheckForDirection(const cinder::app::KeyEvent& event);
  void SetUpMap(std::string map_line);


 private:
  mylibrary::Engine engine_;
  const size_t size_;

  std::vector<mylibrary::Map> game_maps_;

  std::vector<std::vector<char>> map_;

  bool is_move_right_ = true;
  bool is_move_left_ = true;
  bool is_move_up_ = true;
  bool is_move_down_ = true;

  cinder::audio::VoiceRef background_audio_file;
  int player_move_state = 0;
};

}  // namespace myapp

#endif  // FINALPROJECT_APPS_MYAPP_H_
