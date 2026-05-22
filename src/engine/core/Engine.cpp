#include "Engine.hpp"
#include "../../game/constants.hpp"
#include "../graphics/Renderer.hpp"
#include "../input/InputManager.hpp"

Engine::Engine() = default;

bool Engine::Init() {
  romfsInit();
  aptInit();

  // initialize the renderer
  m_renderer = std::make_unique<Renderer>();
  m_renderer->Init(Renderer::InitMode::CONSOLE_BOTTOM);

  // To move the cursor you have to print "\x1b[r;cH", where r and c are respectively
  // the row and column where you want your cursor to move
  // The top screen has 30 rows and 50 columns
  // The bottom screen has 30 rows and 40 columns
  printf("\x1b[8;15HHello World!");
  printf("\x1b[11;10HThis is a %s", APP_NAME);
  printf("\x1b[15;12HPress Start to exit.");

  return true;
}

Engine::~Engine() {
  // Graceful hardware shutdown order
  //
  // destroy the renderer
  m_renderer.reset();

  // exit others
  aptExit();
  romfsExit();
}

bool Engine::isRunning() const {
  // aptMainLoop checks if the OS wants the application to close (Home menu press)
  return aptMainLoop();
}

void Engine::update() {
  // Read input registers
  InputManager::update();
}

void Engine::nextFrame() {
  m_renderer->prepareFrame();
}

void Engine::endFrame() {
  m_renderer->finishFrame();
}
