//
// Created by Aniruddha Pai on 4/18/20.
//

#include "zelda/player.h"

#include <iostream>
#include <fstream>

#include <nlohmann/json.hpp>

#include <cinder/Font.h>
#include <cinder/Text.h>
#include <cinder/gl/draw.h>
#include <cinder/gl/gl.h>
#include <cinder/app/App.h>

using namespace std;
using nlohmann::json;
#if defined(CINDER_COCOA_TOUCH)
const char kNormalFont[] = "Arial";
const char kBoldFont[] = "Arial-BoldMT";
const char kDifferentFont[] = "VCR OSD Mono";
#elif defined(CINDER_LINUX)
const char kNormalFont[] = "Arial Unicode MS";
const char kBoldFont[] = "Arial Unicode MS";
const char kDifferentFont[] = "VCR OSD Mono";
#else
const char kNormalFont[] = "Arial";
const char kBoldFont[] = "Arial Bold";
const char kDifferentFont[] = "VCR OSD Mono";
#endif

namespace zelda {

Player::Player(Location location)
  : loc_{location} {}

void Player::SetLoc(Location set_loc) { loc_ = set_loc; }

Location Player::GetLoc() const { return loc_; }

void Player::SetCurrentHealth(int set_current_health) {
  current_health_ = set_current_health;
}

int Player::GetCurrentHealth() { return current_health_; }

void Player::SetMoneyAmount(int set_money_amount) {
  total_money_ = set_money_amount;
}

int Player::GetMoneyAmount() { return total_money_; }

void Player::SetMonstersKilled(int monsters_killed) {
  monsters_killed_ = monsters_killed;
}

void Player::AddInfoToMenu() {
  json j;

  j = {
      {"Player Name", "Link"},
      {"Max Health", max_health_},
      {"Current Health", current_health_},
      {"Monsters Killed", monsters_killed_},
      {"Money", total_money_}
  };

  std::ofstream add_to_menu("menu.json");
  add_to_menu << j << std::endl;
}

void PrintMenuText(const std::string& text, const int pos, const int xi,
                   const int yi, const int xj, const int yj) {

  cinder::gl::color(cinder::Color::black());

  const cinder::vec2 loc = cinder::app::getWindowCenter();
  const cinder::ivec2 size = {500, 50};

  auto box = cinder::TextBox()
      .alignment(cinder::TextBox::LEFT)
      .font(cinder::Font(kDifferentFont, 30))
      .size(size)
      .backgroundColor(cinder::ColorA(0, 0, 0, 0))
      .text(text);

  const auto box_size = box.getSize();
  const auto surface = box.render();
  const auto texture = cinder::gl::Texture::create(surface);
  cinder::gl::draw(texture, cinder::Rectf(((loc.x/pos) + xi),
                                          ((loc.y/pos) + yi),
                                          ((loc.x/pos) + xj),
                                          ((loc.y/pos) + yj)));
}

void Player::ViewMenu() {
  std::ifstream read_menu("menu.json");

  json j;
  read_menu >> j;

  PrintMenuText(std::to_string(j["Max Health"].get<int>()),
                20, 345, 65, 1325, 130);
  PrintMenuText(std::to_string(j["Current Health"].get<int>()),
                20, 345, 255, 1325, 320);
  PrintMenuText(std::to_string(j["Monsters Killed"].get<int>()),
                20, 357, 432, 1337, 497);
  PrintMenuText(std::to_string(j["Money"].get<int>()),
                20, 1005, 743, 1985, 808);
  PrintMenuText(j["Player Name"].get<std::string>(),
                20, 1172, 623, 2162, 688);
}

} // namespace zelda