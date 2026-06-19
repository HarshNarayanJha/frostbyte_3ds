#include "engine/core/Engine.hpp"
#include "engine/input/InputManager.hpp"
#include "engine/util/Logger.hpp"

#include "game/Game.hpp"
#include "game/states/GameState.hpp"

int main() {
  Logger::setLevel(Logger::LogLevel::DEBUG);
  Logger::debug("main application boot");

  // Standard fixed step time context for 3DS rendering loops (~60Hz)
  const float dt = 1.0f / 60.0f;

  Game    game;
  Engine &engine = game.getEngine();

  while (engine.isRunning()) {
    // engine must be updated first
    engine.update();

    if (game.getState() == GameState::MAIN_MENU) {
      if (InputManager::isDown(KEY_START)) {
        Logger::info("Exiting application");
        break;
      }
    }

    // first update then draw
    game.update(dt);

    engine.nextFrame();
    {
      game.draw();
    }
    engine.endFrame();
  }

  return 0;
}
