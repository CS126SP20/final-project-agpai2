// Copyright (c) 2020 CS126SP20. All rights reserved.

#ifndef FINALPROJECT_APPS_MYAPP_H_
#define FINALPROJECT_APPS_MYAPP_H_

#include <cinder/app/App.h>
#include <cinder/app/KeyEvent.h>
#include <cinder/audio/Voice.h>
#include <zelda/direction.h>
#include <zelda/engine.h>
#include <zelda/location.h>
#include <zelda/map.h>
#include <zelda/monster.h>

namespace zeldaapp {

const int kCharacterSize = 70;
const int kAttackLinkSize = 100;
const float kRatio = 1.43;

const int kRowTiles = 13;
const int kColTiles = 21;

const int kFullScreenHeight = 900;
const int kFullScreenWidth = 1440;

class Zelda : public cinder::app::App {
 public:
  Zelda();
  void setup() override;
  void update() override;
  void draw() override;
  void keyDown(cinder::app::KeyEvent) override;

 private:
  // Plays the game's background theme
  void PlayBackgroundTheme();

  // Draws the player
  void DrawPlayer();

  // Draws the monster
  void DrawMonster();

  // Draws attacking link
  void DrawAttackLink();

  // Draws the game screen's background
  void DrawBackground();

  // Displays the Pause menu screen
  void DisplayMenu();

  // Plays the treasure sound
  void PlayTreasureSound();

  // Different directions are assigned and set based on link's
  // current positon.
  void CheckForDirection(const cinder::app::KeyEvent& event);

  // This is to reset link's position after a screen transition
  void ResetPosition(zelda::Location location);

 private:
  zelda::Engine player_engine_;
  zelda::Map mapper_;
  const size_t size_;

  zelda::Monster monster_;

  // This is done to keep track of time, while the game is paused
  std::chrono::time_point<std::chrono::system_clock> last_intact_time_;
  std::chrono::time_point<std::chrono::system_clock> last_pause_time_;
  bool is_game_paused_;

  // The current map the player is on
  std::string curr_map_;

  // The bool values are to check for the possible directions
  bool is_move_right_ = true;
  bool is_move_left_ = true;
  bool is_move_up_ = true;
  bool is_move_down_ = true;

  bool is_attack_ = false;

  zelda::Direction player_move_state_;

  cinder::audio::VoiceRef background_audio_file_;
  cinder::audio::VoiceRef treasure_audio_file_;
};

}  // namespace zeldaapp

#endif  // FINALPROJECT_APPS_MYAPP_H_
