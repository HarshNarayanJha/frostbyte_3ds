#pragma once

#include <3ds.h>

enum class GameState : u8 {
  NONE,      // no state change
  MAIN_MENU, // in main menu
  LEVEL,     // transition to some level
};

struct StateRequest {
  GameState state = GameState::NONE;
  int       data  = 0; // optional data, otherwise 0

  StateRequest()  = default;
  StateRequest(GameState s) : state(s) {}
  StateRequest(GameState s, int d) : state(s), data(d) {}
};
