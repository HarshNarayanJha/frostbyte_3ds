#pragma once

#include "states/GameState.hpp"
#include <memory>

class Engine;
class Screen;

class Game {
public:
  Game();
  ~Game();

  void changeState(GameState state);

  Engine &getEngine() {
    return *m_engine;
  }

  void update(float dt);
  void draw();

private:
  std::unique_ptr<Engine> m_engine;

  std::unique_ptr<Screen> m_activeScreen;
};
