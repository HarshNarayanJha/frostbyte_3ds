#pragma once

#include "../math/Math.hpp"
#include "../math/Rect.hpp"
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

  void drawHollowRect(const Rect &rect, u32 colorT, u32 colorR, u32 colorB, u32 colorL, float thickness = 1.0f,
                      float z = 0.5f) {
    drawLine({rect.left(), rect.top()}, {rect.right(), rect.top()}, colorT, thickness, z);
    drawLine({rect.right(), rect.top()}, {rect.right(), rect.bottom()}, colorR, thickness, z);
    drawLine({rect.right(), rect.bottom()}, {rect.left(), rect.bottom()}, colorB, thickness, z);
    drawLine({rect.left(), rect.bottom()}, {rect.left(), rect.top()}, colorL, thickness, z);
  }

  void drawHollowCircle(const Vec2 &pos, float radius, u32 colorTL, u32 colorTR, u32 colorBL, u32 colorBR,
                        float z = 0.5f) {
    C2D_DrawCircle(pos.x, pos.y, z, radius, colorTL, colorTR, colorBL, colorBR);
  }

  void drawTriangle(const Vec2 &pos, float size, u32 color, float z = 0.5f) {
    float halfSize = size / 2.0f;
    Vec2  p1       = pos + Vec2(halfSize, 0.0f);
    Vec2  p2       = pos + Vec2(-halfSize, halfSize);
    Vec2  p3       = pos + Vec2(-halfSize, -halfSize);

    C2D_DrawTriangle(p1.x, p1.y, color, p2.x, p2.y, color, p3.x, p3.y, color, z);
  }

  void drawLine(const Vec2 &start, const Vec2 &end, u32 color, float thickness = 1.0f, float z = 0.5f) {
    C2D_DrawLine(start.x, start.y, color, end.x, end.y, color, thickness, z);
  }
};
