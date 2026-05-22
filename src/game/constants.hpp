#pragma once

#include <citro2d.h>

#define APP_NAME "Frostbyte 3DS"
#define SCREEN_WIDTH 400
#define SCREEN_HEIGHT 240
#define BORDER_WIDTH 2

constexpr float SPEED            = 300.0f;
constexpr float ACCELERATION     = 200.0f;
constexpr float DECELERATION     = 50.0f;
constexpr float GRAVITY_CONSTANT = 1000000.0f;

/* Colors */
const u32 clrClear  = C2D_Color32(0xFF, 0xFF, 0xFF, 0xFF);
const u32 clrBg     = C2D_Color32(0x12, 0x12, 0x12, 0xFF);

const u32 clrBlack  = C2D_Color32(0, 0, 0, 255);

const u32 clrWhite  = C2D_Color32(0xFF, 0xFF, 0xFF, 0xFF);

const u32 clrRed    = C2D_Color32(0xFF, 0x00, 0x00, 0xFF);
const u32 clrOrange = C2D_Color32(0xFF, 0x7F, 0x00, 0xFF);
const u32 clrYellow = C2D_Color32(0xFF, 0xFF, 0x00, 0xFF);
const u32 clrGreen  = C2D_Color32(0x00, 0xFF, 0x00, 0xFF);
const u32 clrBlue   = C2D_Color32(0x00, 0x00, 0xFF, 0xFF);
const u32 clrIndigo = C2D_Color32(0x4B, 0x00, 0x82, 0xFF);
const u32 clrViolet = C2D_Color32(0x9A, 0x0E, 0xEA, 0xFF);
