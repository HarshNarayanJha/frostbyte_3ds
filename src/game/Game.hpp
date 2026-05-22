#pragma once

#include <memory>
#include <vector>

class Engine;
class Player;
class Block;
class Snowflake;

class Game {
public:
  Game(Player player, std::vector<Block> blocks, std::vector<Snowflake> snowflakes);
  ~Game();

  Engine &getEngine() {
    return *m_engine;
  }

  void update(float dt);
  void draw();

private:
  std::unique_ptr<Engine> m_engine;

  std::unique_ptr<Player> m_player;
  std::vector<Block> m_blocks;
  std::vector<Snowflake> m_snowflakes;
};
