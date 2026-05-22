#pragma once

#include "../math/Math.hpp"
#include <citro2d.h>

/**
 * Renders graphics using the Citro2D library. Provides static methods for drawing various shapes.
 */
class Renderer {
private:
  C3D_RenderTarget *m_topScreen{};
  C3D_RenderTarget *m_bottomScreen{};

public:
  Renderer();
  ~Renderer();

  enum InitMode : u8 { CONSOLE_TOP, CONSOLE_BOTTOM, CONSOLE_NONE };
  bool Init(InitMode mode);

  C3D_RenderTarget *getTopScreen() const {
    return m_topScreen;
  }
  C3D_RenderTarget *getBottomScreen() const {
    return m_bottomScreen;
  }

  void prepareFrame();
  void finishFrame();

  void drawRect(const Vec2 &pos, const Vec2 &size, u32 color, float z = 0.5f) {
    C2D_DrawRectSolid(pos.x, pos.y, z, size.x, size.y, color);
  }

  void drawCircle(const Vec2 &pos, float radius, u32 color, float z = 0.5f) {
    C2D_DrawCircleSolid(pos.x, pos.y, z, radius, color);
  }

  void drawHollowRect(const Vec2 &pos, const Vec2 &size, u32 colorTL, u32 colorTR, u32 colorBL, u32 colorBR,
                      float z = 0.5f) {
    C2D_DrawRectangle(pos.x, pos.y, z, size.x, size.y, colorTL, colorTR, colorBL, colorBR);
  }

  void drawHollowCircle(const Vec2 &pos, float radius, u32 colorTL, u32 colorTR, u32 colorBL, u32 colorBR,
                        float z = 0.5f) {
    C2D_DrawCircle(pos.x, pos.y, z, radius, colorTL, colorTR, colorBL, colorBR);
  }
};
