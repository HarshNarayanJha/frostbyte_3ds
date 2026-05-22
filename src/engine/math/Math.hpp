#pragma once

#include <cmath>

/**
 * Represents a Vector with two dimensions, x and y.
 */
struct Vec2 {
  float x = 0.0f;
  float y = 0.0f;

  Vec2()  = default;
  constexpr Vec2(float x, float y) : x(x), y(y) {}

  Vec2 operator+(const Vec2 &other) const {
    return {x + other.x, y + other.y};
  }
  Vec2 operator*(float scalar) const {
    return {x * scalar, y * scalar};
  }

  Vec2 operator-(const Vec2 &other) const {
    return {x - other.x, y - other.y};
  }

  Vec2 &operator+=(const Vec2 &other) {
    x += other.x;
    y += other.y;
    return *this;
  }

  Vec2 &operator*=(float scalar) {
    x *= scalar;
    y *= scalar;
    return *this;
  }

  Vec2 moveTowards(const Vec2 &target, float maxDistance) const {
    Vec2  direction = target - *this;
    float distance  = direction.len();
    if (distance <= maxDistance) {
      return target;
    }
    return *this + (direction * (maxDistance / distance));
  }

  float len() const {
    return std::sqrt((x * x) + (y * y));
  }

  float lenSquared() const {
    return (x * x) + (y * y);
  }
};
