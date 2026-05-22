#pragma once

#include "Math.hpp"

struct Rect {
  Vec2 pos;
  Vec2 size;

  Rect() : pos(0.0f, 0.0f), size(0.0f, 0.0f) {};
  Rect(Vec2 pos, Vec2 size) : pos(pos), size(size) {};

  float left() const {
    return pos.x;
  };
  float right() const {
    return pos.x + size.x;
  };
  float top() const {
    return pos.y;
  };
  float bottom() const {
    return pos.y + size.y;
  };
};
