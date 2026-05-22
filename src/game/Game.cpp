#include "Game.hpp"
#include "constants.hpp"

Game::Game(Player player, std::vector<Block> blocks) : m_player(player), m_blocks(blocks) {
  m_engine = std::make_unique<Engine>();
  m_engine->Init();
}

Game::~Game() {
  m_engine.reset();
}

void Game::update(float dt) {
  m_player.update(dt);

  for (auto &bk : m_blocks) {
    bk.update(dt);
  }
}

void Game::draw() {
  // Render Top Screen Geometry
  // TODO: Move to Renderer
  C2D_TargetClear(m_engine->getRenderer().getTopScreen(), clrWhite); // Clear screen to White
  C2D_SceneBegin(m_engine->getRenderer().getTopScreen());

  // draw the player first, otherwise it won't show up, due to some reason
  // even though the examples say otherwise, circles must be drawn last
  m_player.draw(m_engine->getRenderer());

  // then draw the blocks
  for (auto &bk : m_blocks) {
    bk.draw(m_engine->getRenderer());
  }

  // Render Bottom Screen UI (not yet, it's console for now)
  // C2D_TargetClear(bottom, C2D_Color32(240, 240, 240, 255));
  // C2D_SceneBegin(bottom);
}
