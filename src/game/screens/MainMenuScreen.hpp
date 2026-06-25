#pragma once

#include "../../engine/math/Rect.hpp"
#include "../constants.hpp"
#include "../states/Screen.hpp"

class MainMenuScreen : public Screen {
public:
  MainMenuScreen();
  ~MainMenuScreen() override;

  StateRequest update(float dt) override;
  void         draw(Renderer &renderer) override;

  u32 getClearColor() const override {
    return clrBg;
  }

private:
  Rect toprect  = {Vec2((SCREEN_WIDTH / 2.0f) - 60.0f, SCREEN_HEIGHT / 6.0f), Vec2(120, 60)};
  Rect playRect = {Vec2((SCREEN_WIDTH / 2.0f) - 30.0f, SCREEN_HEIGHT / 2.0f), Vec2(60, 25)};
  Rect exitRect = {Vec2((SCREEN_WIDTH / 2.0f) - 30.0f, SCREEN_HEIGHT / 1.5f), Vec2(60, 25)};
};
