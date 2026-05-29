#pragma once

#include "Math.hpp"

struct Rect {
  Vec2 pos;
  Vec2 size;

  Rect() : pos(0.0f, 0.0f), size(0.0f, 0.0f) {};
  Rect(Vec2 pos, Vec2 size) : pos(pos), size(size) {};

  /**
   * Returns the left edge of the rectangle. (x-coordinate)
   */
  float left() const {
    return pos.x;
  };
  /**
   * Returns the right edge of the rectangle. (x-coordinate)
   */
  float right() const {
    return pos.x + size.x;
  };
  /**
   * Returns the top edge of the rectangle. (y-coordinate)
   */
  float top() const {
    return pos.y;
  };
  /**
   * Returns the bottom edge of the rectangle. (y-coordinate)
   */
  float bottom() const {
    return pos.y + size.y;
  };
};
