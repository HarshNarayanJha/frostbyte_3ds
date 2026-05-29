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
  direction.normalize();

  if (direction.lenSquared() > 0) {
    m_vel = m_vel.moveTowards(direction * m_speed, m_accel * dt);
  } else {
    m_vel = m_vel.moveTowards(Vec2(0, 0), m_decel * dt);
  }

  m_pos.x += m_vel.x * dt;
  m_pos.y += m_vel.y * dt;
}

void Player::collideWorldBoundary() {

  if (getRect().left() < 0.0f) {
    m_pos.x = 0.0f + m_size;
    m_vel.x = -m_vel.x * m_bounciness;
  } else if (getRect().right() > SCREEN_WIDTH) {
    m_pos.x = SCREEN_WIDTH - m_size;
    m_vel.x = -m_vel.x * m_bounciness;
  }

  if (getRect().top() < 0.0f) {
    m_pos.y = 0.0f + m_size;
    m_vel.y = -m_vel.y * m_bounciness;
  } else if (getRect().bottom() > SCREEN_HEIGHT) {
    m_pos.y = SCREEN_HEIGHT - m_size;
    m_vel.y = -m_vel.y * m_bounciness;
  }
}

void Player::draw(Renderer &renderer) {
  renderer.drawCircle(m_pos, m_size, clrBlack);

  if (DEBUG_DRAW_VELOCITY) {
    float length = m_vel.len();
    if (length > 0) {
      float scaledLength = length / SPEED * m_size;
      Vec2  dirPoint     = m_pos + m_vel.normalized() * scaledLength;
      renderer.drawLine(m_pos, dirPoint, clrRed);
    }
  }

  if (DEBUG_DRAW_BBOX) {
    renderer.drawHollowRect(getRect(), clrOrange, clrOrange, clrOrange, clrOrange);
  }
}

void Player::bounce(const Rect &other, const Vec2 &hitPoint) {
  // TODO: Receive normal instead and do a proper mirror
  // separating axis resolution
  // https://www.youtube.com/watch?v=dn0hUgsok9M&t=300s

  if (m_vel.x > 0) { // moving right
    m_vel.x = -m_vel.x * m_bounciness;
  } else if (m_vel.x < 0) { // moving left
    m_vel.x = -m_vel.x * m_bounciness;
  }

  if (m_vel.y > 0) { // moving down
    m_vel.y = -m_vel.y * m_bounciness;
  } else if (m_vel.y < 0) { // moving up
    m_vel.y = -m_vel.y * m_bounciness;
  }
}

void Player::applyDelta(Vec2 delta) {
  m_pos += delta;
}

Vec2 Player::getPos() const {
  return m_pos;
}

Vec2 Player::getVel() const {
  return m_vel;
}

Rect Player::getRect() const {
  Vec2 tl = m_pos - Vec2(m_size, m_size);
  return {
      tl, {m_size * 2.0f, m_size * 2.0f}
  };
}

float Player::getSize() const {
  return m_size;
}
