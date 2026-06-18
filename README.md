# Frostbyte 3DS

Save your Christmas! Collect the Snowflakes

## Architectural Notes

```
main
 └── Engine
      ├── Renderer
      ├── InputManager
      ├── Audio
      └── Scene
           └── Player
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
syscall. This makes the bottom screen or any other console available for `printf`-ing.
