#include "Player.hpp"
#include "../../engine/graphics/Renderer.hpp"
#include "../../engine/input/InputManager.hpp"
#include "../constants.hpp"

Player::Player(float x, float y, float size, float speed) : m_pos(x, y), m_size(size), m_vel(0, 0), m_speed(speed) {}

void Player::update(float dt) {
  float accel    = 300.0f;
  float friction = 0.950f;

  if (InputManager::isHeld(KEY_UP))
    m_vel.y -= accel * dt;
  if (InputManager::isHeld(KEY_DOWN))
    m_vel.y += accel * dt;
  if (InputManager::isHeld(KEY_LEFT))
    m_vel.x -= accel * dt;
  if (InputManager::isHeld(KEY_RIGHT))
    m_vel.x += accel * dt;

  // Apply sliding damping/friction
  m_vel.x *= friction;
  m_vel.y *= friction;

  m_pos.x += m_vel.x * dt;
  m_pos.y += m_vel.y * dt;
}

void Player::draw(Renderer &renderer) {
  renderer.drawCircle(m_pos, m_size / 2.0f, clrBlack);
}
