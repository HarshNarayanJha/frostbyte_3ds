#include "Renderer.hpp"
#include "../util/Logger.hpp"

Renderer::Renderer() = default;

bool Renderer::Init(Renderer::InitMode mode) {
  Logger::info("Renderer::Init");

  // init renderer somehow
  gfxInitDefault();

  if (!C3D_Init(C3D_DEFAULT_CMDBUF_SIZE)) {
    Logger::error("C3D_Init failed");
    gfxExit();
    return false;
  }
  if (!C2D_Init(C2D_DEFAULT_MAX_OBJECTS)) {
    Logger::error("C2D_Init failed");
    C3D_Fini();
    gfxExit();
    return false;
  }
  C2D_Prepare();

  switch (mode) {
  case InitMode::CONSOLE_TOP:
    Logger::info("Renderer InitMode::CONSOLE_TOP");

    static PrintConsole topTextConsole;
    consoleInit(GFX_TOP, &topTextConsole);
    consoleSelect(&topTextConsole);

    m_topScreen    = nullptr;
    m_bottomScreen = C2D_CreateScreenTarget(GFX_BOTTOM, GFX_LEFT);
    break;

  case InitMode::CONSOLE_BOTTOM:
    Logger::info("Renderer InitMode::CONSOLE_BOTTOM");

    m_topScreen    = C2D_CreateScreenTarget(GFX_TOP, GFX_LEFT);
    m_bottomScreen = nullptr;

    // Initialize console on bottom screen. Using NULL as the second argument tells the console library to use the
    // internal console structure as current one. Pass a PrintConsole to use it instead.
    static PrintConsole bottomTextConsole;
    consoleInit(GFX_BOTTOM, &bottomTextConsole);
    consoleSelect(&bottomTextConsole);
    break;

  case InitMode::CONSOLE_NONE:
    Logger::info("Renderer InitMode::CONSOLE_NONE");

    m_topScreen    = C2D_CreateScreenTarget(GFX_TOP, GFX_LEFT);
    m_bottomScreen = C2D_CreateScreenTarget(GFX_BOTTOM, GFX_LEFT);
    break;
  }

  return true;
}

Renderer::~Renderer() {
  Logger::info("Renderer::~Renderer teardown");

  C2D_Fini();
  C3D_Fini();
  gfxExit();
}

void Renderer::prepareFrame() {
  // Start 3DS drawing command buffer
  C3D_FrameBegin(C3D_FRAME_SYNCDRAW);
}

void Renderer::finishFrame() {
  // Swap screens and synchronize frame-rate
  C3D_FrameEnd(0);
}
