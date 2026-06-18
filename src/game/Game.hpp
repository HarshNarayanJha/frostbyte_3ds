#pragma once

#include "screens/LevelScreen.hpp"
#include "screens/MainMenuScreen.hpp"
#include "states/GameState.hpp"
#include <memory>
#include <vector>

class Engine;
class Player;
class Block;
class Snowflake;

class Game {
public:
  Game(GameState intial_state, Player player, std::vector<Block> blocks, std::vector<Snowflake> snowflakes);
  ~Game();

  GameState getState() const {
    return m_state;
  }

  void changeState(GameState state);

  Engine &getEngine() {
    return *m_engine;
  }

  void update(float dt);
  void draw();

  /**
   * Resets all the entities handled by the game except the engine
   */
  void reset();

private:
  GameState               m_state;
  std::unique_ptr<Engine> m_engine;

  std::unique_ptr<MainMenuScreen> m_main_menu_screen;
  std::unique_ptr<LevelScreen>    m_level_screen;

  std::unique_ptr<Player> m_player;
  std::vector<Block>      m_blocks;
  std::vector<Snowflake>  m_snowflakes;
};
