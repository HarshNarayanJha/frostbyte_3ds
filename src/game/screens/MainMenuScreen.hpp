#pragma once

#include "../../engine/util/Logger.hpp"

class MainMenuScreen {
public:
  MainMenuScreen() {
    Logger::info("MainMenuScreen::MainMenuScreen init");
  };

  ~MainMenuScreen() {
    Logger::info("MainMenuScreen::~MainMenuScreen teardown");
  };

  void update();
  void draw();
};
