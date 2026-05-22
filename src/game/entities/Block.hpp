#pragma once

#include "../../engine/math/Math.hpp"

class Renderer;

class Block {
private:
  Vec2 m_pos;
  Vec2 m_size;

public:
  Block(float x, float y, float w, float h);
  ~Block() = default;

  void update(float dt);
  void draw(Renderer &renderer);
};
