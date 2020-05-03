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

// These constants are created to adjust the size of the character
const int kCharacterSize = 70;
const int kAttackLinkSize = 100;
const float kRatio = 1.43;

// These constants are the number of tiles in a row and column of a screen
const int kRowTiles = 13;
const int kColTiles = 21;

// These constants are dimensions of a full size screen
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
  // Different directions are assigned and set based on link's
  // current positon.
  void CheckForDirection(const cinder::app::KeyEvent& event);

  // Displays the Pause menu screen
  void DisplayMenu();

  // Draws the game screen's background
  void DrawBackground();

  // Draws the player
  void DrawPlayer();

  // Draws attacking link
  void DrawAttackLink();

  // Draws the monster
  void DrawMonster();

  // Plays the game's background theme
  void PlayBackgroundTheme();

  // Plays the treasure sound
  void PlayTreasureSound();

  // This is to reset link's position after a screen transition
  void ResetPosition(zelda::Location location);

 private:
  zelda::Engine player_engine_;
  zelda::Map mapper_;
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

  // This is to keep track of player direction
  zelda::Direction player_direction_;

  // These are to play the audio files
  cinder::audio::VoiceRef background_audio_file_;
  cinder::audio::VoiceRef treasure_audio_file_;
};

}  // namespace zeldaapp

#endif  // FINALPROJECT_APPS_MYAPP_H_
