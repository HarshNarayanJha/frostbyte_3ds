#pragma once

#include "../math/Math.hpp"

#include <3ds.h>
#include <citro2d.h>

/**
 * InputManager handles input state and provides methods for querying input state.
 */
class InputManager {
public:
  /**
   * Scans for input and updates the direction. Call once every frame.
   */
  static void update() {
    hidScanInput();
    m_keysHeld = hidKeysHeld();
    m_keysDown = hidKeysDown();

    // dpad
    float dX = static_cast<float>(isHeld(KEY_DRIGHT) - isHeld(KEY_DLEFT));
    float dY = static_cast<float>(isHeld(KEY_DDOWN) - isHeld(KEY_DUP));

    // cpad
    circlePosition cpad;
    hidCircleRead(&cpad);

    float cX = C2D_Clamp(cpad.dx / 150.0f, -1.0f, 1.0f);
    float cY = C2D_Clamp(-cpad.dy / 150.0f, -1.0f, 1.0f);

    // deadzone
    if (std::abs(cX) < 0.1f)
      cX = 0.0f;
    if (std::abs(cY) < 0.1f)
      cY = 0.0f;

    Vec2  combined(dX + cX, dY + cY);
    float len = combined.len();
    if (len > 1.0f) {
      combined.normalize();
    }

    m_direction = combined;
  };

  static Vec2 direction() {
    return m_direction;
  }

  /**
   * Returns whether the given key is currently held down (atleast since last frame).
   */
  static bool isHeld(u32 key) {
    return m_keysHeld & key;
  }
  /**
   * Returns whether the given key was pressed down this frame (new).
   */
  static bool isDown(u32 key) {
    return m_keysDown & key;
  }

private:
  inline static u32 m_keysHeld   = 0;
  inline static u32 m_keysDown   = 0;

  inline static Vec2 m_direction = {0.0f, 0.0f};
};
