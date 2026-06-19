#pragma once

#include <3ds.h>

enum class GameState : u8 {
  NONE,      // no state change
  MAIN_MENU, // in main menu
  LEVEL,     // transition to some level
};
