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

  case GameState::NONE:
    Logger::error("Game::changeState called with NONE!");
    svcBreak(UserBreakType::USERBREAK_ASSERT);
    break;

  default:
    Logger::error("Game::changeState: Unhandled GameState %d", static_cast<int>(request.state));
    svcBreak(UserBreakType::USERBREAK_ASSERT);
    break;
  }

  if (!m_activeScreen) {
    Logger::error("Game::changeState: m_activeScreen is null!");
    svcBreak(UserBreakType::USERBREAK_ASSERT);
  }

  m_state = request.state;
}

void Game::update(float dt) {
  if (!m_activeScreen)
    return;
  Logger::trace("Game::update dt=%.4f", dt);

  if (m_fadeState == FadeState::FADE_OUT) {
    m_fadeAlpha += m_fadeSpeed * dt;
    if (m_fadeAlpha >= 255.0f) {
      m_fadeAlpha = 255.0f;

      if (m_pendingRequest.state == GameState::NONE) {
        Logger::error("Game::draw: FADE_OUT finished, but pending request is NONE");
        svcBreak(UserBreakType::USERBREAK_ASSERT);
      }
      // swap to the pending state
      changeState(m_pendingRequest);

      m_pendingRequest = {GameState::NONE};
      m_fadeState      = FadeState::FADE_IN;
    }
    return; // freeze

  } else if (m_fadeState == FadeState::FADE_IN) {
    m_fadeAlpha -= m_fadeSpeed * dt;
    if (m_fadeAlpha <= 0.0f) {
      m_fadeAlpha = 0.0f;
      m_fadeState = FadeState::NONE;
    }
    // game still runs
  }

  StateRequest requestedState = m_activeScreen->update(dt);
  if (requestedState.state != GameState::NONE && m_fadeState == FadeState::NONE) {
    m_pendingRequest = requestedState;
    m_fadeAlpha      = 0.0f;
    m_fadeState      = FadeState::FADE_OUT;
  }
}

void Game::draw() {
  Renderer &renderer = m_engine->getRenderer();
  Logger::trace("Game::draw");

  u32 clearColor = m_activeScreen ? m_activeScreen->getClearColor() : clrClear;
  // Render Top Screen Geometry
  renderer.clear(renderer.getTopScreen(), clearColor);
  C2D_SceneBegin(renderer.getTopScreen());

  if (m_activeScreen) {
    m_activeScreen->draw(renderer);
  }

  if (m_fadeState != FadeState::NONE) {
    Logger::debug("Game::draw: fadeState=%d, fadeAlpha=%.2f", static_cast<int>(m_fadeState), m_fadeAlpha);
    u8  r         = (m_fadeColor >> 16) & 0xFF;
    u8  g         = (m_fadeColor >> 8) & 0xFF;
    u8  b         = m_fadeColor & 0xFF;
    u32 fadeColor = C2D_Color32(r, g, b, static_cast<u8>(m_fadeAlpha));

    renderer.drawFade(fadeColor);
  }
}
