#include "Snowflake.hpp"
#include "../../engine/graphics/Renderer.hpp"
#include "../../engine/math/Math.hpp"
#include "../../engine/math/Rect.hpp"

#include "../constants.hpp"

Snowflake::Snowflake(float x, float y, float size) : m_pos(x, y), m_size(size) {}

void Snowflake::update(float dt) {}

void Snowflake::draw(Renderer &renderer) {
  renderer.drawTriangle(m_pos, m_size, clrBlue);

  if (DEBUG_DRAW_BBOX) {
    renderer.drawHollowRect(getRect(), clrOrange, clrOrange, clrOrange, clrOrange);
  }
}

void Snowflake::consume() {
  // proper dispose later
  m_size = 0.0f;
}

Rect Snowflake::getRect() const {
  Vec2 tl = m_pos - Vec2(m_size / 2.0f, m_size / 2.0f);
  return {
      tl, {m_size, m_size}
  };
}
