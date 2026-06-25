#include "MainMenuScreen.hpp"
#include "../../engine/graphics/Renderer.hpp"
#include "../../engine/input/InputManager.hpp"
#include "../../engine/math/Rect.hpp"
#include "../../engine/util/Logger.hpp"
#include "../constants.hpp"
#include "../states/GameState.hpp"
#include <3ds.h>

MainMenuScreen::MainMenuScreen() {
  Logger::info("MainMenuScreen::MainMenuScreen init");
}

MainMenuScreen::~MainMenuScreen() {
  Logger::info("MainMenuScreen::~MainMenuScreen teardown");
}

StateRequest MainMenuScreen::update(float dt) {
  // listen to clicks on rects and change state
  if (InputManager::isDown(KEY_A)) {
    // change state to level
    Logger::debug("KEY_A pressed on MainMenuScreen. Progressing to level 1.");
    return {GameState::LEVEL, 1};
  }

  return {};
}

void MainMenuScreen::draw(Renderer &renderer) {
  renderer.clear(renderer.getTopScreen(), clrBg);

  renderer.drawRect(toprect.pos, toprect.size, clrBlue);

  renderer.drawRect(playRect.pos, playRect.size, clrGreen);
  renderer.drawRect(exitRect.pos, exitRect.size, clrRed);
}
