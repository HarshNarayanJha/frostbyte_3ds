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
  m_player->collideWorldBoundary();

  for (auto &bk : m_blocks) {
    bk.update(dt);
  }

  for (auto &sf : m_snowflakes) {
    sf.update(dt);
  }

  // TODO: Improve and check collisions with blocks failling within a certain threshold of player's bounding box
  // Which is skewed towards player's velocity vector, for now, check with all of them.

  // check collisions with blocks
  for (auto &bk : m_blocks) {
    Vec2  nearestPoint = Collision::getNearestPointOnRect(m_player->getPos(), bk.getRect());
    Vec2  rayToNearest = nearestPoint - m_player->getPos();
    float overlap      = m_player->getSize() - rayToNearest.len();

    if (std::isnan(overlap))
      overlap = 0.0f;

    if (overlap > 0) {
      m_player->applyDelta(-rayToNearest.normalized() * overlap);
      m_player->bounce(bk.getRect(), nearestPoint);

      bk.setLastCollisionPoint(nearestPoint);
    }
  }

  for (auto &sf : m_snowflakes) {
    if (Collision::checkAABB(m_player->getRect(), sf.getRect())) {
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

    if (DEBUG_DRAW_COLLISION_NEAREST_POINT) {
      Vec2 nearestPoint = Collision::getNearestPointOnRect(m_player->getPos(), bk.getRect());

      C2D_DrawCircleSolid(nearestPoint.x, nearestPoint.y, 0.5f, 2.0f, clrGreen);
      C2D_DrawLine(
          m_player->getPos().x, m_player->getPos().y, clrRed, nearestPoint.x, nearestPoint.y, clrGreen, 1.0f, 0.5f);
    }
  }

  // then draw the snowflakes
  for (auto &sf : m_snowflakes) {
    sf.draw(m_engine->getRenderer());
  }

  // Render Bottom Screen UI (not yet, it's console for now)
  // C2D_TargetClear(bottom, C2D_Color32(240, 240, 240, 255));
  // C2D_SceneBegin(bottom);
}
