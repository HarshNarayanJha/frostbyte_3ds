#include "Game.hpp"

#include "../engine/core/Engine.hpp"
#include "../engine/util/Logger.hpp"
#include "constants.hpp"
#include "data/LevelRegistry.hpp"
#include "screens/LevelScreen.hpp"
#include "screens/MainMenuScreen.hpp"
#include "states/GameState.hpp"

#include <3ds.h>
#include <memory>

Game::Game() {
  Logger::info("Game::Game init");

  m_engine = std::make_unique<Engine>();
  m_engine->Init();

  changeState({GameState::MAIN_MENU});
}

Game::~Game() {
  Logger::info("Game::~Game teardown");
}

void Game::changeState(StateRequest request) {
  Logger::trace("Game::changeState %d with data=%d", static_cast<int>(request.state), request.data);

  switch (request.state) {
  case GameState::MAIN_MENU:
    Logger::info("Game::changeState state=MainMenu");
    m_activeScreen = std::make_unique<MainMenuScreen>();
    break;

  case GameState::LEVEL:
    Logger::info("Game::changeState state=InLevel data=%d", request.data);
    m_activeScreen = std::make_unique<LevelScreen>(LevelRegistry::getLevel(request.data));
    break;

  default:
    Logger::error("Game::changeState: Unhandled GameState %d", static_cast<int>(request.state));
    svcBreak(UserBreakType::USERBREAK_ASSERT);
    break;
  }

  m_state = request.state;
}

void Game::update(float dt) {
  if (!m_activeScreen)
    return;
  Logger::trace("Game::update dt=%.4f", dt);

  StateRequest requestedState = m_activeScreen->update(dt);
  if (requestedState.state != GameState::NONE) {
    changeState(requestedState);
  }
}

void Game::draw() {
  Logger::trace("Game::draw");

  // Render Top Screen Geometry
  m_engine->getRenderer().clear(m_engine->getRenderer().getTopScreen(), clrClear);
  C2D_SceneBegin(m_engine->getRenderer().getTopScreen());

  if (m_activeScreen) {
    m_activeScreen->draw(m_engine->getRenderer());
  }
}
