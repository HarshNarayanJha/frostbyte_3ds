#pragma once

#include "../../../engine/math/Math.hpp"
#include <3ds.h>
#include <vector>

class Renderer;

struct DieParticle {
  Vec2  pos;
  Vec2  vel;
  float size;
  float rotation;
  u32   color;

  float shrinkRate;
};

class DieEffect {
private:
  float m_duration;
  float m_timer = 0.0f;
  Vec2  m_origin;

  std::vector<DieParticle> m_particles;

  void addParticle(const Vec2 &direction, float startSize, u32 color, float shrinkRate);

public:
  DieEffect(float duration, Vec2 pos);

  bool update(float dt);
  void draw(Renderer &renderer);
};
