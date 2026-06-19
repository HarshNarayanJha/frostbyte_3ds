#pragma once

#include "../../engine/math/Math.hpp"
#include <vector>

typedef struct {
  float x, y, width, height;
} BlockData;

typedef struct {
  float x, y, size;
} SnowflakeData;

typedef struct {
  int                        levelId;
  Vec2                       playerSpawn;
  std::vector<BlockData>     blocks;
  std::vector<SnowflakeData> snowflakes;
} LevelData;
