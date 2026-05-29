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

  float m_bounciness = 0.8f;

public:
  Player(float x, float y, float size, float speed, float accel, float decel, float gravity);
  ~Player() = default;

  /**
   * Updates the player's position and velocity based on input and gravity.
   * Called every frame.
   */
  void update(float dt);

  /**
   * Resolves the player's collision with the world boundary, bouncing off if necessary.
   * Called every frame if collision with world bounds is required.
   */
  void collideWorldBoundary();

  /**
   * Draws the player on the screen using the provided renderer.
   * Called every frame.
   */
  void draw(Renderer &renderer);

  /**
   * Bounces off the velocity vector based on the collision rect and hit point.
   */
  void bounce(const Rect &other, const Vec2 &hitPoint);

  /**
   * Applies a delta vector to the player's position, adjusting it accordingly.
   */
  void applyDelta(Vec2 delta);

  Vec2  getPos() const;
  Vec2  getVel() const;
  Rect  getRect() const;
  float getSize() const;
};
