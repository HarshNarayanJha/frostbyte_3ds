#include "sprites.hpp"

#include <3ds.h>
#include <citro2d.h>
#include <citro3d.h>
#include <stdio.h>

#define SCREEN_WIDTH 400
#define SCREEN_HEIGHT 240
#define BORDER_WIDTH 10

int main() {
  romfsInit();
  aptInit();
  gfxInitDefault();

  C3D_Init(C3D_DEFAULT_CMDBUF_SIZE);
  C2D_Init(C2D_DEFAULT_MAX_OBJECTS);
  C2D_Prepare();

  // Initialize console on top screen. Using NULL as the second argument tells the console library
  // to use the internal console structure as current one
  consoleInit(GFX_BOTTOM, nullptr);

  C3D_RenderTarget* top = C2D_CreateScreenTarget(GFX_TOP, GFX_LEFT);
  // C3D_RenderTarget* bottom = C2D_CreateScreenTarget(GFX_BOTTOM, GFX_LEFT);

  // To move the cursor you have to print "\x1b[r;cH", where r and c are respectively
  // the row and column where you want your cursor to move
  // The top screen has 30 rows and 50 columns
  // The bottom screen has 30 rows and 40 columns
  printf("\x1b[8;15HHello World!");
  printf("\x1b[11;10HThis is a Frostbyte 3DS");
  printf("\x1b[15;12HPress Start to exit.");

  // load the spritesheet
  C2D_SpriteSheet sheet = C2D_SpriteSheetLoad("romfs:/gfx/sprites.t3x");
  if (!sheet) {
    svcBreak(USERBREAK_PANIC);
  }

  // load the icon sprite
  C2D_Sprite sprite;
  C2D_SpriteFromSheet(&sprite, sheet, sprites_fan_idx);
  C2D_SpriteSetCenter(&sprite, 0.5, 0.5);
  C2D_SpriteSetPos(&sprite, SCREEN_WIDTH * 0.5, SCREEN_HEIGHT * 0.5);
  // C2D_SpriteSetScale(&sprite, 0.5, 0.5);

  const u32 clrClear              = C2D_Color32(0xFF, 0xFF, 0xFF, 0xFF);
  const u32 clrBg                 = C2D_Color32(0x12, 0x12, 0x12, 0xFF);

  const u32 clrWhite              = C2D_Color32(0xFF, 0xFF, 0xFF, 0xFF);

  const u32 clrRed                = C2D_Color32(0xFF, 0x00, 0x00, 0xFF);
  const u32 clrOrange             = C2D_Color32(0xFF, 0x7F, 0x00, 0xFF);
  const u32 clrYellow             = C2D_Color32(0xFF, 0xFF, 0x00, 0xFF);
  const u32 clrGreen              = C2D_Color32(0x00, 0xFF, 0x00, 0xFF);
  const u32 clrBlue               = C2D_Color32(0x00, 0x00, 0xFF, 0xFF);
  const u32 clrIndigo             = C2D_Color32(0x4B, 0x00, 0x82, 0xFF);
  const u32 clrViolet             = C2D_Color32(0x9A, 0x0E, 0xEA, 0xFF);

  const int numBlocks             = 7;
  const u32 clrsBlocks[numBlocks] = {
      clrRed, clrOrange, clrYellow, clrGreen, clrBlue, clrIndigo, clrViolet};

  // degrees per frame
  float rotationRate = 5.0f;

  while (aptMainLoop()) {
    hidScanInput();
    if (hidKeysDown() & KEY_START)
      break;

    C2D_SpriteRotateDegrees(&sprite, rotationRate);

    C3D_FrameBegin(C3D_FRAME_SYNCDRAW);
    {
      // clear the screen
      C2D_TargetClear(top, clrClear);
      C2D_SceneBegin(top);

      // draw the border
      C2D_DrawRectSolid(0, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, clrWhite);
      C2D_DrawRectSolid(BORDER_WIDTH,
                        BORDER_WIDTH,
                        0,
                        SCREEN_WIDTH - (BORDER_WIDTH * 2),
                        SCREEN_HEIGHT - (BORDER_WIDTH * 2),
                        clrBg);

      for (int i = 0; i < 7; i++) {
        C2D_DrawRectSolid(
            42 + (i * 50), SCREEN_HEIGHT - (SCREEN_HEIGHT / 4.5), 0, 10, 10, clrsBlocks[i]);
      }

      C2D_DrawSprite(&sprite);
    }
    C3D_FrameEnd(0);
  }

  C2D_SpriteSheetFree(sheet);
  C2D_Fini();
  C3D_Fini();
  gfxExit();
  aptExit();
  romfsExit();
  return 0;
}
