#pragma once

#include "../../engine/util/Logger.hpp"

class LevelScreen {
public:
  LevelScreen() {
    Logger::info("LevelScreen::LevelScreen init");
  };

  ~LevelScreen() {
    Logger::info("LevelScreen::~LevelScreen teardown");
  };

  void update();
  void draw();
};
