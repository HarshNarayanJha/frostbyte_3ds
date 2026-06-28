#pragma once

#include "../math/Math.hpp"
#include "../math/Rect.hpp"
#include <citro2d.h>

/**
 * Renders graphics using the Citro2D library. Provides static methods for drawing various shapes.
 */
class Renderer {
public:
  Renderer();
  ~Renderer();

  enum class InitMode : u8 { CONSOLE_TOP, CONSOLE_BOTTOM, CONSOLE_NONE };
  bool Init(InitMode mode);

  C3D_RenderTarget *getTopScreen() const {
    return m_topScreen;
  }
  C3D_RenderTarget *getBottomScreen() const {
    return m_bottomScreen;
  }

  void prepareFrame();
  void finishFrame();

  void clear(C3D_RenderTarget *target, u32 color) {
    C2D_TargetClear(target, color);
  }

  /**
   * Prints text to the console at the specified row and column.
   * If row or col is -1, the text is printed at the current cursor position.
   * The top screen has 30 rows and 50 columns
   * The bottom screen has 30 rows and 40 columns
   */
  void printTextConsole(const char *text, int row = -1, int col = -1);

  /**
   * Clears the text console.
   */
  void clearTextConsole();

  void drawFade(u32 color) {
    // TODO, make them screen width and height properly
    // even better move this to the engine.
    drawRect({0.0f, 0.0f}, {400.0f, 240.0f}, color, 1.0f);
  }

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

private:
  InitMode m_initMode;

  C3D_RenderTarget *m_topScreen{};
  C3D_RenderTarget *m_bottomScreen{};
};
