#include "Renderer.hpp"

Renderer::Renderer() = default;

bool Renderer::Init(Renderer::InitMode mode) {
  // inti renderer somehow
  gfxInitDefault();

  if (!C3D_Init(C3D_DEFAULT_CMDBUF_SIZE)) {
    return false;
  }
  if (!C2D_Init(C2D_DEFAULT_MAX_OBJECTS)) {
    return false;
  }
  C2D_Prepare();

  switch (mode) {
  case CONSOLE_TOP:
    consoleInit(GFX_TOP, nullptr);

    m_topScreen    = nullptr;
    m_bottomScreen = C2D_CreateScreenTarget(GFX_BOTTOM, GFX_LEFT);
    break;

  case CONSOLE_BOTTOM:
    m_topScreen    = C2D_CreateScreenTarget(GFX_TOP, GFX_LEFT);
    m_bottomScreen = nullptr;

    // Initialize console on bottom screen. Using NULL as the second argument tells the console
    // library to use the internal console structure as current one
    consoleInit(GFX_BOTTOM, nullptr);
    break;

  case CONSOLE_NONE:
    m_topScreen    = C2D_CreateScreenTarget(GFX_TOP, GFX_LEFT);
    m_bottomScreen = C2D_CreateScreenTarget(GFX_BOTTOM, GFX_LEFT);
    break;
  }

  return true;
}

Renderer::~Renderer() {
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
