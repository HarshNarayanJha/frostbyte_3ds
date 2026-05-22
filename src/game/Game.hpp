#pragma once

#include "../engine/core/Engine.hpp"
#include "data/Level.hpp"
#include "entities/Block.hpp"
#include "entities/Player.hpp"

#include <memory>
#include <vector>

class Game {
public:
  Game(Player player, std::vector<Block> blocks);
  ~Game();

  Engine &getEngine() {
    return *m_engine;
  }

  void update(float dt);
  void draw();

private:
  std::unique_ptr<Engine> m_engine;

  Player m_player;
  std::vector<Block> m_blocks;
};
