#include "Renderer.hpp"
#include "../util/Logger.hpp"

Renderer::Renderer() = default;

bool Renderer::Init(Renderer::InitMode mode) {
  Logger::info("Renderer::Init");

  m_initMode = mode;
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

void Renderer::printTextConsole(const char *text, int row, int col) {
  if (m_initMode == InitMode::CONSOLE_NONE) {
    Logger::debug("Renderer::printTextConsole called with InitMode::CONSOLE_NONE. Ignoring");
    return;
  }

  // To move the cursor you have to print "\x1b[r;cH", where r and c are respectively
  // the row and column where you want your cursor to move
  // The top screen has 30 rows and 50 columns
  // The bottom screen has 30 rows and 40 columns
  if (row != -1 && col != -1) {
    printf("\x1b[%d;%dH", row, col);
  } else if (row != -1 || col != -1) {
    Logger::debug("Renderer::printTextConsole both row and col must be provided together");
  }

  printf("%s", text);
}

void Renderer::clearTextConsole() {
  if (m_initMode == InitMode::CONSOLE_NONE) {
    Logger::debug("Renderer::clearTextConsole called with InitMode::CONSOLE_NONE. Ignoring");
    return;
  }

  printf("\033[2J");
}
