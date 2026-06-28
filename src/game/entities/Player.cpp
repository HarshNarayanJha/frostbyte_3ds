#include "Player.hpp"
#include "../../engine/graphics/Renderer.hpp"
#include "../../engine/input/InputManager.hpp"
#include "../constants.hpp"

#include "../../engine/math/Math.hpp"
#include "../../engine/math/Rect.hpp"
#include "../../engine/util/Logger.hpp"
#include "effects/DieEffect.hpp"
#include <memory>

Player::Player(float x, float y, float size, float speed, float accel, float decel, float gravity)
    : m_pos(x, y), m_size(size), m_vel(0, 0), m_speed(speed), m_accel(accel), m_decel(decel), m_gravity(gravity) {
  Logger::info("Player::Player init");
}

void Player::update(float dt) {
  if (isDead())
    return;

  if (isDamaged()) {               // process the die effect instead
    if (m_dieEffect->update(dt)) { // mark as dead finally
      Logger::debug("Player::update die effect finished. Marking as died.");
      m_state = State::DEAD;
    }

    return;
  }

  Vec2 direction = InputManager::direction();
  direction.normalize();

  if (direction.lenSquared() > 0) {
    m_vel = m_vel.moveTowards(direction * m_speed, m_accel * dt);
  } else {
    m_vel = m_vel.moveTowards(Vec2(0, 0), m_decel * dt);
  }

  m_pos.x += m_vel.x * dt;
  m_pos.y += m_vel.y * dt;

  if (m_vel.lenSquared() > 1.0f)
    m_state = State::MOVING;
  else
    m_state = State::IDLE;
}

bool Player::collideWorldBoundary() {
  if (isDamaged() || isDead())
    return false;

  bool collided = false;

  if (getRect().left() < 0.0f) {
    m_pos.x  = 0.0f + m_size;
    m_vel.x  = -m_vel.x * m_bounciness;
    collided = true;
  } else if (getRect().right() > SCREEN_WIDTH) {
    m_pos.x  = SCREEN_WIDTH - m_size;
    m_vel.x  = -m_vel.x * m_bounciness;
    collided = true;
  }

  if (getRect().top() < 0.0f) {
    m_pos.y  = 0.0f + m_size;
    m_vel.y  = -m_vel.y * m_bounciness;
    collided = true;
  } else if (getRect().bottom() > SCREEN_HEIGHT) {
    m_pos.y  = SCREEN_HEIGHT - m_size;
    m_vel.y  = -m_vel.y * m_bounciness;
    collided = true;
  }

  return collided;
}

void Player::draw(Renderer &renderer) {
  if (isDead())
    return;

  if (isDamaged()) {
    // process the die effect instead
    m_dieEffect->draw(renderer);
    return;
  }

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
  if (isDamaged() || isDead())
    return;

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

void Player::damage() {
  if (isDamaged() || isDead())
    return;

  Logger::debug("Player::damage initializing dieEffect and marking damaged");
  m_dieEffect = std::make_unique<DieEffect>(DIE_ANIMATION_DURATION_SECONDS, m_pos);
  m_state     = State::DAMAGED;
  m_vel       = {0, 0};
}

void Player::applyDelta(Vec2 delta) {
  if (isDamaged() || isDead())
    return;

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

bool Player::isDead() const {
  return m_state == State::DEAD;
}

bool Player::isDamaged() const {
  return m_state == State::DAMAGED;
}

bool Player::isAlive() const {
  return m_state == State::IDLE || m_state == State::MOVING;
}
