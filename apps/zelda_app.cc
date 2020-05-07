// Copyright (c) 2020 [Your Name]. All rights reserved.

#include "zelda_app.h"

#include <cinder/app/App.h>
#include <cinder/gl/Texture.h>
#include <cinder/gl/draw.h>
#include <cinder/gl/gl.h>

#if defined(CINDER_COCOA_TOUCH)
const char kNormalFont[] = "VCR OSD Mono";
const char kBoldFont[] = "Arial-BoldMT";
const char kDifferentFont[] = "AmericanTypewriter";
#elif defined(CINDER_LINUX)
const char kNormalFont[] = "VCR OSD Mono";
const char kBoldFont[] = "Arial Unicode MS";
const char kDifferentFont[] = "Purisa";
#else
const char kNormalFont[] = "VCR OSD Mono";
const char kBoldFont[] = "Arial Bold";
const char kDifferentFont[] = "Papyrus";
#endif

namespace zeldaapp {

using cinder::app::KeyEvent;
using cinder::Rectf;

using zelda::Direction;
using zelda::Location;
using zelda::Map;

// This keeps in track the screen that Link is in
int map_num = 0;

// These counts are kept to keep in track the player movements
// and change the animation sprites accordingly
int front_move_count = 0;
int left_move_count = 0;
int right_move_count = 0;
int back_move_count = 0;

int motion_count = 2;

// This count is kept to for a time delay to show Link attack
int attack_count = 0;

// These are the paths that are used to load images for player movements,
// player attacks, show monster movements, and also display the inventory
cinder::fs::path move_path;
cinder::fs::path attack_path;
cinder::fs::path monster_path;
cinder::fs::path inventory_path;

// Stores the name of the player
std::string player_name;

char monster = 'M';
char money = 'C';

bool is_intro_finished;

Zelda::Zelda()
    : player_engine_{kRowTiles, kColTiles},
      monster_{} {}

void Zelda::setup() {
  cinder::gl::disableDepthWrite();
  cinder::gl::disableDepthRead();

  curr_map_ = "screen-H8.png";
  mapper_.ReadImageLabels();
  mapper_.ReadGameScreens();
  maps = mapper_.GetScreen();

  monster_.SetUpMaps(mapper_);

  PlayBackgroundTheme();
  PlayTreasureSound();

  cinder::fs::path movie_path = getAssetPath("zelda-nes-intro.mov");

  if(!movie_path.empty()) {
    PlayGameIntro(movie_path);
  }
}

void Zelda::update() {
  if (is_game_paused_) { return; }

  if(movie_) {
    // This is done to get the movie texture representing the
    // movie's current frame
    movie_texture_ = movie_->getTexture();
  }

  movie_->setRate(1);

  is_intro_finished = false;
  if(!is_intro_finished && movie_->isDone()) {
    is_intro_finished = true;
  }

  curr_map_ = mapper_.GetMapLabels();
  map_num = mapper_.GetNewScreenNum();

  Location location = player_engine_.GetPlayer().GetLoc();

  mapper_.SetGameScreens(monster_.MoveMonster(player_direction_,
      location ,map_num));

  int current_player_health = player_engine_.GetPlayer().GetCurrentHealth();
  if (monster_.IsMonsterAttackLink(location, map_num)) {
    current_player_health--;
    if (current_player_health <= 0) {
      is_player_killed_ = true;
    }
  }

  int money_amount = player_engine_.GetPlayer().GetMoneyAmount();
  if (maps[map_num].coordinates_[location.Col()][location.Row()] == money) {
    maps[map_num].coordinates_[location.Col()][location.Row()] = '0';
    money_amount += 10;
    mapper_.SetGameScreens(maps);
  }

  player_engine_.SetPlayerName(player_name);
  player_engine_.SetPlayerAttributes(current_player_health, money_amount,
      monster_.GetMonstersKilled());

  Location new_player_loc = mapper_.GetPlayerNewLoc(
      mapper_.GetScreen()[map_num],player_engine_);

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


  if (is_intro_finished && !is_game_start_) {
    DrawFileScreen();
    PrintText(player_name, kPosRatio, kXi[0], kYi[0], kXj[0],
        kYj[0]);
  }

  if (!is_intro_finished) {
    if (movie_texture_) {
      cinder::gl::draw(movie_texture_, getWindowBounds());
    }
  } else if (is_game_start_) {
    DrawBackground();
    DrawMoney();
    if (is_game_paused_) {
      DrawMenuScreen();
      return;
    }

    if (!is_attack_) {
      DrawPlayer();
    } else {
      DrawAttackLink();
    }

    DrawMonster();
  }

  if (is_player_killed_) {
    RestartGame();
  }
}

void Zelda::keyDown(KeyEvent event) {
  switch (event.getCode()) {
    case KeyEvent::KEY_UP:
    case KeyEvent::KEY_w: {
      if (!is_game_paused_ && !is_player_killed_) {
        CheckForDirection(event);
        player_direction_ = Direction::kUp;
        back_move_count++;
        player_engine_.PlayerStep();
      }
      break;
    }
    case KeyEvent::KEY_DOWN:
    case KeyEvent::KEY_s: {
      if (!is_game_paused_ && !is_player_killed_) {
        CheckForDirection(event);
        player_direction_ = Direction::kDown;
        front_move_count++;
        player_engine_.PlayerStep();
      }
      break;
    }
    case KeyEvent::KEY_LEFT:
    case KeyEvent::KEY_a: {
      if (!is_game_paused_ && !is_player_killed_) {
        CheckForDirection(event);
        player_direction_ = Direction::kLeft;
        left_move_count++;
        player_engine_.PlayerStep();
      }
      break;
    }
    case KeyEvent::KEY_RIGHT:
    case KeyEvent::KEY_d: {
      if (!is_game_paused_ && !is_player_killed_) {
        CheckForDirection(event);
        player_direction_ = Direction::kRight;
        right_move_count++;
        player_engine_.PlayerStep();
      }
      break;
    }
    case KeyEvent::KEY_p: {
      if (is_intro_finished && is_game_start_) {
        is_game_paused_ = !is_game_paused_;
      }

      if (is_game_paused_) {
        player_engine_.GetPlayer().AddInfoToMenu();
      }
      break;
    }
    case KeyEvent::KEY_SPACE: {
      if (mapper_.IsSwordTaken()) {
        is_attack_ = true;
        monster_.SetIsPlayerAttack(true);
      }
      break;
    }
    case KeyEvent::KEY_RETURN: {
      movie_->setRate(5);
      break;
    }
  }

  if (is_intro_finished && !is_game_start_) {
    player_name += event.getChar();
    if (event.getCode() == KeyEvent::KEY_TAB) {
      player_engine_.SetPlayerName(player_name);
      is_game_start_ = true;
    }
  }

  if (is_player_killed_) {
    if (event.getChar() == 'y') {
      is_player_killed_ = false;
      player_engine_.SetPlayerAttributes(
          player_engine_.GetPlayer().GetMaxHealth(),
          player_engine_.GetPlayer().GetMoneyAmount(),
          monster_.GetMonstersKilled());
    } else if (event.getChar() == 'n') {
      is_player_killed_ = false;
      std::cout << "The Game has ended" << std::endl;
      exit(0);
    }
  }

}

void Zelda::CheckForDirection(const cinder::app::KeyEvent& event) {

  if (is_intro_finished && is_game_start_) {
    if (is_move_up_ && (event.getCode() == KeyEvent::KEY_UP ||
                        event.getCode() == KeyEvent::KEY_w)) {
      player_engine_.SetDirection(Direction::kUp);
      return;
    } else {
      player_engine_.SetDirection(Direction::kNull);
    }

    if (is_move_down_ && (event.getCode() == KeyEvent::KEY_DOWN ||
                          event.getCode() == KeyEvent::KEY_s)) {
      player_engine_.SetDirection(Direction::kDown);
      return;
    } else {
      player_engine_.SetDirection(Direction::kNull);
    }

    if (is_move_left_ && (event.getCode() == KeyEvent::KEY_LEFT ||
                          event.getCode() == KeyEvent::KEY_a)) {
      player_engine_.SetDirection(Direction::kLeft);
      return;
    } else {
      player_engine_.SetDirection(Direction::kNull);
    }

    if (is_move_right_ && (event.getCode() == KeyEvent::KEY_RIGHT ||
                           event.getCode() == KeyEvent::KEY_d)) {
      player_engine_.SetDirection(Direction::kRight);
      return;
    } else {
      player_engine_.SetDirection(Direction::kNull);
    }
  }
}

void Zelda::DrawFileScreen() {
  cinder::fs::path name_path = cinder::fs::path("file-screen.png");
  cinder::gl::Texture2dRef texture = cinder::gl::Texture2d::create(
      loadImage(loadAsset(name_path)));

  cinder::gl::draw(texture, getWindowBounds());
}

void Zelda::DrawMenuScreen() {
  if (mapper_.IsSwordTaken()) {
    inventory_path = cinder::fs::path("inventory-1.png");
  } else {
    inventory_path = cinder::fs::path("inventory-2.png");
  }

  cinder::fs::path menu_path = cinder::fs::path(inventory_path);
  cinder::gl::Texture2dRef texture = cinder::gl::Texture2d::create(
      loadImage(loadAsset(menu_path)));


  cinder::gl::draw(texture, getWindowBounds());

  player_engine_.GetPlayer().ViewMenu();
}

void Zelda::DrawBackground() {
  cinder::gl::Texture2dRef texture = cinder::gl::Texture2d::create(
      loadImage(loadAsset(curr_map_)));

  cinder::gl::draw(texture, getWindowBounds());
}

void Zelda::DrawMoney() {
  Location loc = player_engine_.GetPlayer().GetLoc();

  cinder::fs::path money_path = cinder::fs::path("rupee.png");

  cinder::gl::Texture2dRef texture = cinder::gl::Texture2d::create(
      loadImage(loadAsset(money_path)));

  for (int i = 0; i < kRowTiles; i++) {
    for (int j = 0; j < kColTiles; j++) {
      if (maps[map_num].coordinates_[i][j] == money) {
        cinder::gl::draw(texture, Rectf((kCharacterSize * j *
        getWindowWidth()/kFullScreenWidth),(kCharacterSize * i *
        getWindowHeight()/kFullScreenHeight),(kCharacterSize * j *
            getWindowWidth()/kFullScreenWidth) + kCharacterSize,
                (kCharacterSize * i *
                getWindowHeight()/kFullScreenHeight) + kCharacterSize));
      }
    }
  }
}

void Zelda::DrawPlayer() {
  const Location loc = player_engine_.GetPlayer().GetLoc();

  if (player_direction_ == Direction::kDown) {
    if (front_move_count % motion_count == 0) {
      move_path = cinder::fs::path("link-front-1.png");
    } else {
      move_path = cinder::fs::path("link-front-2.png");
    }
  } else if (player_direction_ == Direction::kUp) {
    if (back_move_count % motion_count == 0) {
      move_path = cinder::fs::path("link-back-1.png");
    } else {
      move_path = cinder::fs::path("link-back-2.png");
    }
  } else if (player_direction_ == Direction::kLeft) {
    if (left_move_count % motion_count == 0) {
      move_path = cinder::fs::path("link-left-1.png");
    } else {
      move_path = cinder::fs::path("link-left-2.png");
    }
  } else if (player_direction_ == Direction::kRight) {
    if (right_move_count % motion_count == 0) {
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

void Zelda::DrawAttackLink() {
  const Location loc = player_engine_.GetPlayer().GetLoc();

  if (player_direction_ == Direction::kDown) {
    attack_path = cinder::fs::path("link-attack-front.png");
  } else if (player_direction_ == Direction::kUp) {
    attack_path = cinder::fs::path("link-attack-back.png");
  } else if (player_direction_ == Direction::kLeft) {
    attack_path = cinder::fs::path("link-attack-left.png");
  } else if (player_direction_ == Direction::kRight) {
    attack_path = cinder::fs::path("link-attack-right.png");
  }

  cinder::gl::Texture2dRef texture = cinder::gl::Texture2d::create(
      loadImage(loadAsset(attack_path)));

  cinder::gl::draw(texture, Rectf((kAttackLinkSize *
  (loc.Row()/kRatio) * getWindowWidth()/kFullScreenWidth),
      (kAttackLinkSize * (loc.Col()/kRatio) *
      getWindowHeight()/kFullScreenHeight),
      (kAttackLinkSize * (loc.Row()/kRatio) *
      getWindowWidth()/kFullScreenWidth) + kAttackLinkSize,
      (kAttackLinkSize * (loc.Col()/kRatio) *
      getWindowHeight()/kFullScreenHeight) + kAttackLinkSize));

  attack_count++;

  if (attack_count % 5 == 0) {
    is_attack_ = false;
    attack_count = 0;
  }
}

void Zelda::DrawMonster() {
  monster_path = cinder::fs::path("octorok-right-1.png");

  if (monster_.GetMonsterDirection() == Direction::kUp) {
    monster_path = cinder::fs::path("octorok-up-1.png");
  } else if (monster_.GetMonsterDirection() == Direction::kDown) {
    monster_path = cinder::fs::path("octorok-down-1.png");
  } else if (monster_.GetMonsterDirection() == Direction::kLeft) {
    monster_path = cinder::fs::path("octorok-left-1.png");
  } else if (monster_.GetMonsterDirection() == Direction::kRight) {
    monster_path = cinder::fs::path("octorok-right-1.png");
  }
  cinder::gl::Texture2dRef texture = cinder::gl::Texture2d::create(
      loadImage(loadAsset(monster_path)));

  for (int i = 0; i < kRowTiles; i++) {
    for (int j = 0; j < kColTiles; j++) {
      if (mapper_.GetScreen()[map_num].coordinates_[i][j] == monster) {
        cinder::gl::draw(texture, Rectf((kCharacterSize * j *
        getWindowWidth()/kFullScreenWidth),
            (kCharacterSize * i * getWindowHeight()/kFullScreenHeight),
            (kCharacterSize * j * getWindowWidth()/kFullScreenWidth) +
            kCharacterSize,
            (kCharacterSize * i * getWindowHeight()/kFullScreenHeight) +
            kCharacterSize));
      }
    }
  }
}

void Zelda::PlayBackgroundTheme() {
  auto background_theme_path = "zelda.mp3";

  auto source_file = cinder::audio::load
      (cinder::app::loadAsset(background_theme_path));
  background_audio_file_ = cinder::audio::Voice::create(source_file);

  if (is_intro_finished) {
    background_audio_file_->start();
  }
}

void Zelda::PlayTreasureSound() {
  auto treasure_theme_path = "treasure.mp3";

  auto source_file = cinder::audio::load
      (cinder::app::loadAsset(treasure_theme_path));
  treasure_audio_file_ = cinder::audio::Voice::create(source_file);
}

void Zelda::PlayGameIntro(const cinder::fs::path& path) {
  movie_ = cinder::qtime::MovieGl::create(path);
  movie_->play();

  movie_texture_.reset();
}

void Zelda::ResetPosition(Location location) {
  if (mapper_.IsScreenChange()) {
    player_engine_.Reset(location);
  }
}

void Zelda::RestartGame() {
  int i = 1;
  PrintText("Game Over", kPosRatio, kXi[i], kYi[i], kXj[i], kYj[i]);
  i++;
  PrintText("Do You Want To Continue?", kPosRatio, kXi[i], kYi[i], kXj[i],
      kYj[i]);
  i++;
  PrintText("Yes or No", kPosRatio, kXi[i], kYi[i], kXj[i], kYj[i]);
}

void Zelda::PrintText(const std::string& text, const int pos, const int xi,
                      const int yi, const int xj, const int yj) {

  const cinder::vec2 loc = cinder::app::getWindowCenter();
  const cinder::ivec2 size = {500, 50};

  auto box = cinder::TextBox()
      .alignment(cinder::TextBox::LEFT)
      .font(cinder::Font(kNormalFont, kPosRatio))
      .size(size)
      .color(cinder::Color::black())
      .backgroundColor(cinder::ColorA(0, 0, 0,
                                      0))
      .text(text);

  const auto box_size = box.getSize();

  const auto surface = box.render();
  const auto texture = cinder::gl::Texture::create(surface);
  cinder::gl::draw(texture, cinder::Rectf(((loc.x/pos) + xi) *
  cinder::app::getWindowWidth()/kFullScreenWidth,
  ((loc.y/pos) + yi) * cinder::app::getWindowHeight()/kFullScreenHeight,
  ((loc.x/pos) + xj) * cinder::app::getWindowWidth()/kFullScreenWidth,
  ((loc.y/pos) + yj) * cinder::app::getWindowHeight()/kFullScreenHeight));
}

}  // namespace zeldaapp
