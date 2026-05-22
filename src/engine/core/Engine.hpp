#pragma once

#include "../graphics/Renderer.hpp"
#include <3ds.h>

#include <memory>

/**
 * Core Engine class. Manages the game loop and renderer.
 */
class Engine {
private:
  std::unique_ptr<Renderer> m_renderer;

public:
  Engine();
  ~Engine();

  Renderer &getRenderer() {
    return *m_renderer;
  }

  /**
   * Initializes the engine and renderer.
   * @return true if initialization was successful, false otherwise.
   */
  bool Init();

  /**
   * Returns whether the engine is currently running.
   */
  bool isRunning() const;

  /**
   * Updates the game state. Updates input
   */
  void update();

  /**
   * Prepares for the next frame of the game loop.
   * Call at the very start of loop before rendering anything.
   */
  void nextFrame();

  /**
   * Ends the current frame of the game loop.
   * Call at the very end of loop after rendering everything.
   */
  void endFrame();
};
