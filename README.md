# Frostbyte 3DS

Save your Christmas! Collect the Snowflakes

## About

Frostbyte 3DS is a port of my game [Frostbyte](https://harshnarayanjha.itch.io/frostbyte) to the Nintendo 3DS.

## Architectural Notes

```
main.cpp
Game
  ├─ Engine (init, update, input polling)
  │  ├─ Math (Vec and Rect)
  │  ├─ Physics (Collison)
  │  ├─ Renderer (Citro2D graphics)
  │  └─ InputManager (static key state)
  │
  └─ Screen
     ├─ MainMenuScreen
     └─ LevelScreen
        ├─ Player
        ├─ Blocks[]
        └─ Snowflakes[]
```

# Build Instructions

Run

```
make
```

and watch the magic happen.

---

Generated using [cookiecutter-3ds-homebrew](https://github.com/HarshNarayanJha/cookiecutter-3ds-homebrew).

## Notes

### Engine

There is a game-agnostic engine framework inside `src/engine` which contains core engine, renderer, input, math, physics
and logging libraries, wrapping citro2d, citro3d and libctru libraries.

### Logging

The logging system in `src/engine/util/logger.hpp` logs directly to the debugger console using `svcOutputDebugString`
syscall. This makes the bottom screen or any other printconsole device available for `printf`-ing.
