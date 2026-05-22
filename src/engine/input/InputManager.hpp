#pragma once

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
    m_keysHeld = hidKeysHeld();
    m_keysDown = hidKeysDown();
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
  inline static u32 m_keysHeld = 0;
  inline static u32 m_keysDown = 0;
};
