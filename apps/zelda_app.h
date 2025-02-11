// Copyright (c) 2020 CS126SP20. All rights reserved.

#ifndef FINALPROJECT_APPS_MYAPP_H_
#define FINALPROJECT_APPS_MYAPP_H_

#include <cinder/app/App.h>
#include <cinder/app/KeyEvent.h>
#include <cinder/audio/Voice.h>

#include <cinder/gl/Texture.h>
#include <cinder/gl/gl.h>
#include <cinder/Surface.h>
#include <cinder/app/RendererGl.h>
#include <cinder/qtime/QuickTimeGl.h>

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

// To maintain relative position of text on screen
const int kPosRatio = 20;

// These constants are maintained to set bounds of a text box
// in player inventory
const int kXi[4] = {275, 500, 300, 500};
const int kXj[4] = {1475, 1900, 1900, 1900};
const int kYi[4] = {143, 75, 350, 550};
const int kYj[4] = {341, 525, 500, 700};

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

  // Displays the File Screen, where the user can choose his/her name
  void DrawFileScreen();

  // Displays the Pause menu screen
  void DrawMenuScreen();

  // Draws the game screen's background
  void DrawBackground();

  // Draws the money on the screen
  void DrawMoney();

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

  // Plays the game intro scene
  void PlayGameIntro(const cinder::fs::path &path);

  // This is to reset link's position after a screen transition
  void ResetPosition(zelda::Location location);

  // This restarts the game
  void RestartGame();

  // Prints the text on the cinder screen
  void PrintText(const std::string& text, int pos, int xi, int yi, int xj,
      int yj);

 private:
  zelda::Engine player_engine_;
  zelda::Map mapper_;
  zelda::Monster monster_;

  // This is done to check the game state, ie; playing or paused
  bool is_game_paused_ = false;

  // The current map the player is on
  std::string curr_map_;

  // Maintains a copy of all the maps
  std::vector<zelda::Map> maps;

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

  // These are to maintain the movie textures and play the movie
  cinder::gl::TextureRef movie_texture_;
  cinder::qtime::MovieGlRef movie_;

  // Checks if the game has started
  bool is_game_start_ = false;

  // Checks if the player is killed
  bool is_player_killed_ = false;
};

}  // namespace zeldaapp

#endif  // FINALPROJECT_APPS_MYAPP_H_
