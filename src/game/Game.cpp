#include "Game.hpp"

#include "../engine/core/Engine.hpp"
#include "../engine/util/Logger.hpp"
#include "constants.hpp"
#include "screens/LevelScreen.hpp"
#include "screens/MainMenuScreen.hpp"

#include <3ds.h>
#include <memory>

Game::Game() {
  Logger::info("Game::Game init");

  m_engine = std::make_unique<Engine>();
  m_engine->Init();

  changeState(GameState::MAIN_MENU);
}

Game::~Game() {
  Logger::info("Game::~Game teardown");
}

void Game::changeState(GameState state) {
  Logger::trace("Game::changeState %d", static_cast<int>(state));

  switch (state) {
  case GameState::MAIN_MENU:
    Logger::info("Game::changeState state=MainMenu");
    m_activeScreen = std::make_unique<MainMenuScreen>();
    break;

  case GameState::LEVEL:
    Logger::info("Game::changeState state=InLevel");
    m_activeScreen = std::make_unique<LevelScreen>();
    break;

  default:
    Logger::error("Unhandled GameState %d", static_cast<int>(state));
    svcBreak(UserBreakType::USERBREAK_ASSERT);
    break;
  }
}

void Game::update(float dt) {
  if (!m_activeScreen)
    return;
  Logger::trace("Game::update dt=%.4f", dt);

  GameState requestedState = m_activeScreen->update(dt);
  if (requestedState != GameState::NONE) {
    changeState(requestedState);
  }
}

void Game::draw() {
  Logger::trace("Game::draw");

  // Render Top Screen Geometry
  C2D_TargetClear(m_engine->getRenderer().getTopScreen(), clrClear);
  C2D_SceneBegin(m_engine->getRenderer().getTopScreen());

  if (m_activeScreen) {
    m_activeScreen->draw(m_engine->getRenderer());
  }
}
