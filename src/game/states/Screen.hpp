#pragma once

#include "GameState.hpp"

class Renderer;

class Screen {
public:
  virtual ~Screen()                             = default;

  virtual StateRequest update(float dt)         = 0;
  virtual void         draw(Renderer &renderer) = 0;

  virtual u32 getClearColor() const             = 0;
};
