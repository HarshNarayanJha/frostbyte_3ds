#pragma once

#include "../math/Math.hpp"

/**
 * AABB (Axis-Aligned Bounding Box) collision detection struct.
 */
struct AABB {
  /**
   * Checks if two AABBs are colliding.
   */
  static bool checkCollision(const Vec2 &posA, const Vec2 &sizeA, const Vec2 &posB, const Vec2 &sizeB) {
    return posA.x < posB.x + sizeB.x &&
           posA.x + sizeA.x > posB.x &&
           posA.y < posB.y + sizeB.y &&
           posA.y + sizeA.y > posB.y;
  }
};
