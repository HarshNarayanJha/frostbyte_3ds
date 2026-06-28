#pragma once

#include <citro2d.h>

#define APP_NAME "Frostbyte 3DS"

constexpr float SCREEN_WIDTH     = 400.0f;
constexpr float SCREEN_HEIGHT    = 240.0f;

constexpr float PLAYER_RADIUS    = 8.0f;
constexpr float SPEED            = 200.0f;
constexpr float ACCELERATION     = 100.0f;
constexpr float DECELERATION     = 25.0f;
constexpr float GRAVITY_CONSTANT = 1000000.0f;

#define DEBUG_DRAW_BBOX false
#define DEBUG_DRAW_VELOCITY false
#define DEBUG_DRAW_COLLISION_NEAREST_POINT false
#define DEBUG_DRAW_COLLISION_HIT_POINT false

/* Colors */
const u32 clrClear     = C2D_Color32(0xFF, 0xFF, 0xFF, 0xFF);
const u32 clrBg        = C2D_Color32(0x12, 0x12, 0x12, 0xFF);

const u32 clrBlack     = C2D_Color32(0x00, 0x00, 0x00, 0xFF);
const u32 clrBlackSemi = C2D_Color32(0x00, 0x00, 0x00, 0x60);

const u32 clrWhite     = C2D_Color32(0xFF, 0xFF, 0xFF, 0xFF);

const u32 clrRed       = C2D_Color32(0xFF, 0x00, 0x00, 0xFF);
const u32 clrOrange    = C2D_Color32(0xFF, 0x7F, 0x00, 0xFF);
const u32 clrYellow    = C2D_Color32(0xFF, 0xFF, 0x00, 0xFF);
const u32 clrGreen     = C2D_Color32(0x00, 0xFF, 0x00, 0xFF);
const u32 clrBlue      = C2D_Color32(0x00, 0x00, 0xFF, 0xFF);
const u32 clrIndigo    = C2D_Color32(0x4B, 0x00, 0x82, 0xFF);
const u32 clrViolet    = C2D_Color32(0x9A, 0x0E, 0xEA, 0xFF);
