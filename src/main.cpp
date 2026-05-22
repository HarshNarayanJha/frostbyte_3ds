#include "engine/core/Engine.hpp"
#include "engine/input/InputManager.hpp"
#include "game/Game.hpp"
#include "game/constants.hpp"
#include "game/entities/Block.hpp"

#include <memory>

int main() {
  std::vector<Block> blocks;
  blocks.emplace_back(10.0f, 10.0f, 10.0f, 10.0f);
  blocks.emplace_back(SCREEN_WIDTH - 80.0f, SCREEN_HEIGHT - 80.0f, 50.0f, 30.0f);

  // Standard fixed step time context for 3DS rendering loops (~60Hz)
  const float dt             = 1.0f / 60.0f;

  std::unique_ptr<Game> game = std::make_unique<Game>(Player{80.0f, SCREEN_HEIGHT / 2.0f, 15.0f, 20.0f}, blocks);
  Engine &engine             = game->getEngine();

  while (engine.isRunning()) {
    engine.update();
    if (InputManager::isDown(KEY_START)) {
      break;
    }

    game->update(dt);

    engine.nextFrame();
    {
      game->draw();
    }
    engine.endFrame();
  }

  return 0;
}
