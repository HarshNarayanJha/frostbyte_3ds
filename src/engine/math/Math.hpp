#pragma once

/**
 * Represents a Vector with two dimensions, x and y.
 */
struct Vec2 {
  float x = 0.0f;
  float y = 0.0f;

  Vec2()  = default;
  Vec2(float x, float y) : x(x), y(y) {}

  Vec2 operator+(const Vec2 &other) const {
    return {x + other.x, y + other.y};
  }
  Vec2 operator*(float scalar) const {
    return {x * scalar, y * scalar};
  }
};
