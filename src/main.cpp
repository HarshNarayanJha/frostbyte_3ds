#include "engine/core/Engine.hpp"
#include "engine/input/InputManager.hpp"

#include "game/Game.hpp"
#include "game/constants.hpp"
#include "game/entities/Block.hpp"
#include "game/entities/Player.hpp"
#include "game/entities/Snowflake.hpp"

#include <memory>

int main() {
  std::vector<Block> blocks;

  // world boundary
  blocks.emplace_back(0.0f, -10.0f, SCREEN_WIDTH, 10.0f);        // top
  blocks.emplace_back(0.0f, SCREEN_HEIGHT, SCREEN_WIDTH, 10.0f); // bottom
  blocks.emplace_back(-10.0f, 0.0f, 10.0f, SCREEN_HEIGHT);       // left
  blocks.emplace_back(SCREEN_WIDTH, 0.0f, 10.0f, SCREEN_HEIGHT); // right

  blocks.emplace_back(10.0f, 10.0f, 10.0f, 10.0f);
  blocks.emplace_back(SCREEN_WIDTH - 80.0f, SCREEN_HEIGHT - 80.0f, 50.0f, 30.0f);

  std::vector<Snowflake> snowflakes;
  snowflakes.emplace_back(45.0f, 45.0f, 5.0f);
  snowflakes.emplace_back(SCREEN_WIDTH - 45.0f, SCREEN_HEIGHT - 45.0f, 5.0f);

  // Standard fixed step time context for 3DS rendering loops (~60Hz)
  const float dt             = 1.0f / 60.0f;

  std::unique_ptr<Game> game = std::make_unique<Game>(
      Player{80.0f, SCREEN_HEIGHT / 2.0f, 15.0f, SPEED, ACCELERATION, DECELERATION, GRAVITY_CONSTANT},
      blocks,
      snowflakes);
  Engine &engine = game->getEngine();

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
