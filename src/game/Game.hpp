#pragma once

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
  std::unique_ptr<Engine> m_engine;

  std::unique_ptr<Screen> m_activeScreen;
};
