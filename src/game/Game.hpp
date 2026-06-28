#pragma once

#include "data/GameData.hpp"
#include "states/GameState.hpp"
#include <memory>

class Engine;
class Screen;

class Game {
public:
  Game();
  ~Game();

  GameState getState() const {
    return m_state;
  }

  void changeState(StateRequest state);

  Engine &getEngine() {
    return *m_engine;
  }

  void update(float dt);
  void draw();

private:
  GameState               m_state;
  GameData                m_data;
  std::unique_ptr<Engine> m_engine;

  std::unique_ptr<Screen> m_activeScreen;

  enum class FadeState : u8 { NONE, FADE_IN, FADE_OUT };
  FadeState m_fadeState    = FadeState::NONE;

  u32          m_fadeColor = 0x00000000;
  float        m_fadeAlpha = 0.0f; // 0.0 (clear) to 255.0 (solid)
  float        m_fadeSpeed = 500.0f;
  StateRequest m_pendingRequest; // state to swap to when screen fades out
};
