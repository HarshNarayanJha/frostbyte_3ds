#pragma once

#include "GameState.hpp"

class Renderer;

class Screen {
public:
  virtual ~Screen()                          = default;

  virtual GameState update(float dt)         = 0;
  virtual void      draw(Renderer &renderer) = 0;
};
