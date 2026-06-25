#include "LevelScreen.hpp"
#include "../../engine/graphics/Renderer.hpp"
#include "../../engine/input/InputManager.hpp"
#include "../../engine/physics/Collision.hpp"
#include "../../engine/util/Logger.hpp"
#include "../constants.hpp"
#include "../data/LevelData.hpp"

LevelScreen::LevelScreen(const LevelData &levelData) : m_currentLevelId(levelData.levelId) {
  Logger::info("LevelScreen::LevelScreen init levelId: %d", m_currentLevelId);

  m_player = std::make_unique<Player>(levelData.playerSpawn.x,
                                      levelData.playerSpawn.y,
                                      PLAYER_RADIUS,
                                      SPEED,
                                      ACCELERATION,
                                      DECELERATION,
                                      GRAVITY_CONSTANT);

  m_blocks.reserve(levelData.blocks.size());
  for (const auto &blockData : levelData.blocks) {
    m_blocks.emplace_back(blockData.x, blockData.y, blockData.width, blockData.height);
  }

  m_snowflakes.reserve(levelData.snowflakes.size());
  for (const auto &snowflakeData : levelData.snowflakes) {
    m_snowflakes.emplace_back(snowflakeData.x, snowflakeData.y, snowflakeData.size);
  }
}

LevelScreen::~LevelScreen() {
  Logger::info("LevelScreen::~LevelScreen teardown");
}

StateRequest LevelScreen::update(float dt) {
  Logger::trace("LevelScreen::update");

  // handle reload
  if (InputManager::isDown(KEY_X)) {
    Logger::debug("KEY_X Pressed in Level. Reloading current level.");
    return {GameState::LEVEL, m_currentLevelId};
  }

  // back to main on START or SELECT press.
  // TODO: add pause menu
  if (InputManager::isDown(KEY_START) || InputManager::isDown(KEY_SELECT)) {
    Logger::debug("KEY_START or KEY_SELECT Pressed in Level. Returning to main menu.");
    return {GameState::MAIN_MENU};
  }

  // Progress level on press A
  // TODO: Check actual level progress logic
  if (InputManager::isDown(KEY_A)) {
    Logger::debug("KEY_A Pressed in Level. Progressing to next level.");
    return {GameState::LEVEL, m_currentLevelId + 1};
  }

  if (m_player->isDead()) {
    Logger::debug("LevelScreen::update: Player died. Returning DIE state.");
    return {GameState::LEVEL, m_currentLevelId};
  }

  m_player->update(dt);
  m_player->collideWorldBoundary();

  for (auto &bk : m_blocks) {
    bk.update(dt);
  }

  for (auto &sf : m_snowflakes) {
    sf.update(dt);
  }

  if (!m_player->isDamaged()) {
    // Check collisions with blocks
    for (auto &bk : m_blocks) {
      Vec2  nearestPoint = Collision::getNearestPointOnRect(m_player->getPos(), bk.getRect());
      Vec2  rayToNearest = nearestPoint - m_player->getPos();
      float overlap      = m_player->getSize() - rayToNearest.len();

      if (std::isnan(overlap))
        overlap = 0.0f;

      if (overlap > 0) {
        Logger::debug("Collision detected with block. Overlap: %.4f. Calling .damage() on player.", overlap);
        m_player->damage();

        bk.setLastCollisionPoint(nearestPoint);
      }
    }

    // check if player is colliding with snowflake
    for (auto &sf : m_snowflakes) {
      if (Collision::checkAABB(m_player->getRect(), sf.getRect())) {
        sf.consume();
      }
    }
  }

  return {};
}

void LevelScreen::draw(Renderer &renderer) {
  renderer.clear(renderer.getTopScreen(), clrWhite);

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
