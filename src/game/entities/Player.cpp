#include "Player.hpp"
#include "../../engine/graphics/Renderer.hpp"
#include "../../engine/input/InputManager.hpp"
#include "../constants.hpp"

#include "../../engine/math/Math.hpp"
#include "../../engine/math/Rect.hpp"

Player::Player(float x, float y, float size, float speed, float accel, float decel, float gravity)
    : m_pos(x, y), m_size(size), m_vel(0, 0), m_speed(speed), m_accel(accel), m_decel(decel), m_gravity(gravity) {}

void Player::update(float dt) {
  Vec2 direction = InputManager::direction();

  if (direction.len() > 0) {
    m_vel = m_vel.moveTowards(direction * m_speed, m_accel * dt);
  } else {
    m_vel = m_vel.moveTowards(Vec2(0, 0), m_decel * dt);
  }

  m_pos.x += m_vel.x * dt;
  m_pos.y += m_vel.y * dt;
}

void Player::draw(Renderer &renderer) {
  renderer.drawCircle(m_pos, m_size / 2.0f, clrBlack);
}

void Player::bounce() {
  m_vel *= -1;
}

Rect Player::getRect() const {
  Vec2 tl = m_pos - Vec2(m_size / 2.0f, m_size / 2.0f);
  return {
      tl, {m_size, m_size}
  };
}
