#include "Block.hpp"
#include "../../engine/graphics/Renderer.hpp"
#include "../../engine/math/Math.hpp"
#include "../../engine/math/Rect.hpp"
#include "../constants.hpp"

Block::Block(float x, float y, float w, float h) : m_pos(x, y), m_size(w, h) {}

void Block::update(float dt) {}

void Block::draw(Renderer &renderer) {
  renderer.drawRect(m_pos, m_size, clrBlack);
}

Rect Block::getRect() const {
  return {m_pos, m_size};
}
