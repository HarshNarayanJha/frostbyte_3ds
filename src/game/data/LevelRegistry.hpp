#pragma once

#include "../../engine/util/Logger.hpp"
#include "../constants.hpp"
#include "LevelData.hpp"
#include <unordered_map>

class LevelRegistry {
public:
  static inline const std::unordered_map<int, LevelData> levels{
      {
       1, {
              .levelId     = 1,
              .playerSpawn = {80.0f, SCREEN_HEIGHT / 2.0f},
              .blocks =
                  {
                      {
                          .x      = (SCREEN_WIDTH / 2.0f) - 15.0f,
                          .y      = (SCREEN_HEIGHT / 2.0f) - 25.0f,
                          .width  = 30.0f,
                          .height = 50.0f,
                      },
                      {
                          .x      = SCREEN_WIDTH - 80.0f,
                          .y      = SCREEN_HEIGHT - 80.0f,
                          .width  = 50.0f,
                          .height = 30.0f,
                      },
                  },
              .snowflakes =
                  {
                      {
                          .x    = 45.0f,
                          .y    = 45.0f,
                          .size = 5.0f,
                      },
                      {
                          .x    = SCREEN_WIDTH - 45.0f,
                          .y    = SCREEN_HEIGHT - 45.0f,
                          .size = 5.0f,
                      },
                  },
          }, },
      {2,
       {
           .levelId     = 2,
           .playerSpawn = {SCREEN_WIDTH - 80.0f, SCREEN_HEIGHT / 2.0f},
           .blocks      = {},
           .snowflakes  = {},
       }},
      {3,
       {
           .levelId     = 3,
           .playerSpawn = {SCREEN_WIDTH / 2.0f, SCREEN_HEIGHT / 2.0f},
           .blocks      = {},
           .snowflakes  = {},
       }},
  };

  static LevelData getLevel(int id) {
    Logger::debug("LevelRegistry::getLevel id=%d", id);

    if (id <= 0 || id > static_cast<int>(levels.size())) {
      Logger::error("LevelRegistry::getLevel id=%d is out of bounds. Returning last level", id);
      return levels.at(levels.size()); // safe since levelIds start from 1
    }

    return levels.at(id);
  }
};
