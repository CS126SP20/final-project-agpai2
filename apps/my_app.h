// Copyright (c) 2020 CS126SP20. All rights reserved.

#ifndef FINALPROJECT_APPS_MYAPP_H_
#define FINALPROJECT_APPS_MYAPP_H_

#include <cinder/app/App.h>
#include <mylibrary/engine.h>

namespace myapp {

const int kTileSize = 50;
const int kNumTiles = 16;

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

 private:
  mylibrary::Engine engine_;
  const size_t size_;
};

}  // namespace myapp

#endif  // FINALPROJECT_APPS_MYAPP_H_
