#pragma once

#include <vector>

class Player;
class Block;

typedef struct {
  Player *player;
  std::vector<Block *> blocks;
} LevelData;
