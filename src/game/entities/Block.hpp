#pragma once

#include "../../engine/math/Math.hpp"

class Renderer;
struct Rect;

class Block {
private:
  Vec2 m_pos;
  Vec2 m_size;

  Vec2 m_lastCollisionPoint = {-1, -1};

public:
  Block(float x, float y, float w, float h);
  ~Block() = default;

  void update(float dt);
  void draw(Renderer &renderer);

  Rect getRect() const;

  void setLastCollisionPoint(Vec2 point) {
    m_lastCollisionPoint = point;
  }
  Vec2 getLastCollisionPoint() const {
    return m_lastCollisionPoint;
  }
};
