#pragma once

#include "../../engine/math/Math.hpp"

class Renderer;

class Player {
private:
  Vec2 m_pos;
  float m_size;
  Vec2 m_vel;
  float m_speed;

public:
  Player(float x, float y, float size, float speed);
  ~Player() = default;

  void update(float dt);
  void draw(Renderer &renderer);
};
