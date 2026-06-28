#pragma once

#include "../constants.hpp"
#include "../data/GameData.hpp"
#include "../data/LevelData.hpp"
#include "../entities/Block.hpp"
#include "../entities/Player.hpp"
#include "../entities/Snowflake.hpp"
#include "../states/Screen.hpp"
#include <memory>
#include <vector>

class LevelScreen : public Screen {
public:
  LevelScreen(const LevelData &levelData, GameData &data);
  ~LevelScreen() override;

  StateRequest update(float dt) override;
  void         draw(Renderer &renderer) override;

  u32 getClearColor() const override {
    return clrWhite;
  }

private:
  GameData               &m_data;
  int                     m_currentLevelId;
  std::unique_ptr<Player> m_player;
  std::vector<Block>      m_blocks;
  std::vector<Snowflake>  m_snowflakes;
};
