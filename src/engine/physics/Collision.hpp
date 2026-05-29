#pragma once

#include "../math/Math.hpp"
#include "../math/Rect.hpp"

#include <algorithm>

struct Collision {
  static bool checkAABB(const Rect &a, const Rect &b) {
    return a.left() < b.right() && a.right() > b.left() && a.top() < b.bottom() && a.bottom() > b.top();
  };

  static bool pointInRect(const Vec2 &p, const Rect &r) {
    return p.x >= r.left() && p.x <= r.right() && p.y >= r.top() && p.y <= r.bottom();
  };

  static Vec2 getNearestPointOnRect(const Vec2 &p, const Rect &r) {
    Vec2 nearestPoint;
    nearestPoint.x = std::clamp(p.x, r.left(), r.right());
    nearestPoint.y = std::clamp(p.y, r.top(), r.bottom());
    return nearestPoint;
  }
};
