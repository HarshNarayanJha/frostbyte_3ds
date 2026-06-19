#include "LevelScreen.hpp"
#include "../../engine/graphics/Renderer.hpp"
#include "../../engine/input/InputManager.hpp"
#include "../../engine/physics/Collision.hpp"
#include "../../engine/util/Logger.hpp"
#include "../constants.hpp"
#include <3ds/services/hid.h>

LevelScreen::LevelScreen() {
  Logger::info("LevelScreen::LevelScreen init");

  m_player =
      std::make_unique<Player>(80.0f, SCREEN_HEIGHT / 2.0f, 5.0f, SPEED, ACCELERATION, DECELERATION, GRAVITY_CONSTANT);

  m_blocks.emplace_back((SCREEN_WIDTH / 2.0f) - 15.0f, (SCREEN_HEIGHT / 2.0f) - 25.0f, 30.0f, 50.0f);
  m_blocks.emplace_back(SCREEN_WIDTH - 80.0f, SCREEN_HEIGHT - 80.0f, 50.0f, 30.0f);

  m_snowflakes.emplace_back(45.0f, 45.0f, 5.0f);
  m_snowflakes.emplace_back(SCREEN_WIDTH - 45.0f, SCREEN_HEIGHT - 45.0f, 5.0f);
}

LevelScreen::~LevelScreen() {
  Logger::info("LevelScreen::~LevelScreen teardown");
}

GameState LevelScreen::update(float dt) {
  Logger::trace("LevelScreen::update");

  // back to main on START or SELECT press.
  // TODO: add pause menu
  if (InputManager::isDown(KEY_START) || InputManager::isDown(KEY_SELECT)) {
    return GameState::MAIN_MENU;
  }

  m_player->update(dt);
  m_player->collideWorldBoundary();

  for (auto &bk : m_blocks) {
    bk.update(dt);
  }

  for (auto &sf : m_snowflakes) {
    sf.update(dt);
  }

  // Check collisions with blocks
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

  return GameState::NONE;
}

void LevelScreen::draw(Renderer &renderer) {
  C2D_TargetClear(renderer.getTopScreen(), clrWhite);

  m_player->draw(renderer);

  for (auto &bk : m_blocks) {
    bk.draw(renderer);

    if (DEBUG_DRAW_COLLISION_NEAREST_POINT) {
      Vec2 nearestPoint = Collision::getNearestPointOnRect(m_player->getPos(), bk.getRect());

      C2D_DrawCircleSolid(nearestPoint.x, nearestPoint.y, 0.5f, 2.0f, clrGreen);
      C2D_DrawLine(
          m_player->getPos().x, m_player->getPos().y, clrRed, nearestPoint.x, nearestPoint.y, clrGreen, 1.0f, 0.5f);
    }
  }

  for (auto &sf : m_snowflakes) {
    sf.draw(renderer);
  }
};
