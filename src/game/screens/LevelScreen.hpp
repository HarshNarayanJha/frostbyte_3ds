#pragma once

#include "../entities/Block.hpp"
#include "../entities/Player.hpp"
#include "../entities/Snowflake.hpp"
#include "../states/Screen.hpp"
#include <memory>
#include <vector>

class LevelScreen : public Screen {
public:
  LevelScreen();
  ~LevelScreen() override;

  GameState update(float dt) override;
  void      draw(Renderer &renderer) override;

private:
  std::unique_ptr<Player> m_player;
  std::vector<Block>      m_blocks;
  std::vector<Snowflake>  m_snowflakes;
};
