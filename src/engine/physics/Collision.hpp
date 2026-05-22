#pragma once

#include "../math/Math.hpp"
#include "../math/Rect.hpp"

struct Collision {
  static bool checkAABB(const Rect &a, const Rect &b) {
    return a.left() < b.right() && a.right() > b.left() && a.top() < b.bottom() && a.bottom() > b.top();
  };

  static bool pointInRect(const Vec2 &p, const Rect &r) {
    return p.x >= r.left() && p.x <= r.right() && p.y >= r.top() && p.y <= r.bottom();
  };
};
