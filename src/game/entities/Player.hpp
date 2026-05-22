#pragma once

#include "../../engine/math/Math.hpp"

struct Rect;

class Renderer;

class Player {
private:
  Vec2  m_pos;
  float m_size;
  Vec2  m_vel;
  float m_speed;
  float m_accel;
  float m_decel;
  float m_gravity;

public:
  Player(float x, float y, float size, float speed, float accel, float decel, float gravity);
  ~Player() = default;

  void update(float dt);
  void draw(Renderer &renderer);
  void bounce();

  Rect getRect() const;
};
