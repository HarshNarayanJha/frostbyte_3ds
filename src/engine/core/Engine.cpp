#include "Engine.hpp"
#include "../../game/constants.hpp"
#include "../graphics/Renderer.hpp"
#include "../input/InputManager.hpp"
#include "../util/Logger.hpp"
#include <format>

Engine::Engine() = default;

bool Engine::Init() {
  Logger::info("Engine::Init");
  romfsInit();
  aptInit();

  // initialize the renderer
  m_renderer = std::make_unique<Renderer>();
  m_renderer->Init(Renderer::InitMode::CONSOLE_BOTTOM);

  m_renderer->printTextConsole("Hello World!", 8, 15);
  m_renderer->printTextConsole(std::format("This is {}", APP_NAME).c_str(), 11, 10);
  m_renderer->printTextConsole("Press Select to exit.", 15, 12);

  return true;
}

Engine::~Engine() {
  Logger::info("Engine::~Engine teardown");

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
  Logger::trace("Engine::update");

  // Read input registers
  InputManager::update();
}

void Engine::nextFrame() {
  m_renderer->prepareFrame();
}

void Engine::endFrame() {
  m_renderer->finishFrame();
}
