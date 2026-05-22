#pragma once

#include "../../engine/math/Math.hpp"

struct Rect;
class Renderer;

class Snowflake {
private:
  Vec2  m_pos;
  float m_size;

public:
  Snowflake(float x, float y, float size);
  ~Snowflake() = default;

  void update(float dt);
  void draw(Renderer &renderer);
  void consume();

  Rect getRect() const;
};
