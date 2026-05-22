#include "Game.hpp"

#include "../engine/core/Engine.hpp"
#include "../engine/physics/Collision.hpp"
#include "entities/Block.hpp"
#include "entities/Player.hpp"
#include "entities/Snowflake.hpp"

#include "constants.hpp"

Game::Game(Player player, std::vector<Block> blocks, std::vector<Snowflake> snowflakes)
    : m_blocks(blocks), m_snowflakes(snowflakes) {
  m_engine = std::make_unique<Engine>();
  m_engine->Init();

  m_player = std::make_unique<Player>(player);
}

Game::~Game() {
  m_engine.reset();
}

void Game::update(float dt) {
  // update all
  m_player->update(dt);

  for (auto &bk : m_blocks) {
    bk.update(dt);
  }

  for (auto &sf : m_snowflakes) {
    sf.update(dt);
  }

  // check collisions with blocks
  for (const auto &bk : m_blocks) {
    if (Collision::checkAABB(m_player->getRect(), bk.getRect())) {
      printf("Collision detected with block at (%f, %f)\n", bk.getRect().pos.x, bk.getRect().pos.y);
      m_player->bounce();
    }
  }

  for (auto &sf : m_snowflakes) {
    if (Collision::checkAABB(m_player->getRect(), sf.getRect())) {
      printf("Collision detected with snowflake at (%f, %f)\n", sf.getRect().pos.x, sf.getRect().pos.y);
      sf.consume();
    }
  }
}

void Game::draw() {
  // Render Top Screen Geometry
  // TODO: Move to Renderer
  C2D_TargetClear(m_engine->getRenderer().getTopScreen(), clrWhite); // Clear screen to White
  C2D_SceneBegin(m_engine->getRenderer().getTopScreen());

  // draw the player first, otherwise it won't show up, due to some reason
  // even though the examples say otherwise, circles must be drawn last
  m_player->draw(m_engine->getRenderer());

  // then draw the blocks
  for (auto &bk : m_blocks) {
    bk.draw(m_engine->getRenderer());
  }

  // then draw the snowflakes
  for (auto &sf : m_snowflakes) {
    sf.draw(m_engine->getRenderer());
  }

  // Render Bottom Screen UI (not yet, it's console for now)
  // C2D_TargetClear(bottom, C2D_Color32(240, 240, 240, 255));
  // C2D_SceneBegin(bottom);
}
