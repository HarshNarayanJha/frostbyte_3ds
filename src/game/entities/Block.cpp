#include "Block.hpp"
#include "../../engine/graphics/Renderer.hpp"
#include "../../engine/math/Math.hpp"
#include "../../engine/math/Rect.hpp"
#include "../constants.hpp"

Block::Block(float x, float y, float w, float h) : m_pos(x, y), m_size(w, h) {}

void Block::update(float dt) {
  m_lastCollisionPoint = {-1, -1};
}

void Block::draw(Renderer &renderer) {
  renderer.drawRect(m_pos, m_size, clrBlack);

  if (DEBUG_DRAW_BBOX) {
    renderer.drawHollowRect(getRect(), clrOrange, clrOrange, clrOrange, clrOrange);
  }

  if (DEBUG_DRAW_COLLISION_HIT_POINT && m_lastCollisionPoint.x != -1 && m_lastCollisionPoint.y != -1) {
    renderer.drawCircle(m_lastCollisionPoint, 2.0f, clrGreen);
  }
}

Rect Block::getRect() const {
  return {m_pos, m_size};
}
