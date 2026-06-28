#pragma once

#include "../../engine/util/Logger.hpp"

struct GameData {
  int snowflakes          = 0;
  int snowflakesThisLevel = 0;
  int hits                = 0;
  int dies                = 0;

  float game_seconds      = 0.0;

  int countSnowflake() {
    snowflakesThisLevel++;
    ++snowflakes;
    Logger::debug("GameData::countSnowflake: snowflakesThisLevel: %d, snowflakes: %d", snowflakesThisLevel, snowflakes);
    return snowflakes;
  }

  void resetLevel() {
    snowflakesThisLevel = 0;
    Logger::debug("GameData::resetLevel: snowflakesThisLevel: %d, snowflakes: %d", snowflakesThisLevel, snowflakes);
  }

  void countWallHit() {
    hits++;
    Logger::debug("GameData::countWallHit: hits: %d", hits);
  }

  void countDie() {
    snowflakes -= snowflakesThisLevel;
    snowflakesThisLevel = 0;
    dies++;
    Logger::debug("GameData::countDie: snowflakes: %d, dies: %d", snowflakes, dies);
  }

  void reset() {
    snowflakes          = 0;
    snowflakesThisLevel = 0;
    hits                = 0;
    dies                = 0;
    game_seconds        = 0.0;
    Logger::debug("GameData::reset");
  }
};
