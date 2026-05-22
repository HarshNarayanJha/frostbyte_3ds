#pragma once

#include "../math/Math.hpp"

#include <3ds.h>

/**
 * InputManager handles input state and provides methods for querying input state.
 */
class InputManager {
public:
  /**
   * Scans for input and updates the state. Call once every frame.
   */
  static void update() {
    hidScanInput();
    m_keysHeld  = hidKeysHeld();
    m_keysDown  = hidKeysDown();

    m_direction = {static_cast<float>(isHeld(KEY_RIGHT) - isHeld(KEY_LEFT)),
                   static_cast<float>(isHeld(KEY_DOWN) - isHeld(KEY_UP))};
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
