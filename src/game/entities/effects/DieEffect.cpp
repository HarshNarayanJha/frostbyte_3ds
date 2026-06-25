#include "../../../engine/graphics/Renderer.hpp"
#include "../../../engine/util/Logger.hpp"
#include "../../constants.hpp"
#include <algorithm>

#include "DieEffect.hpp"

void DieEffect::addParticle(const Vec2 &direction, float startSize, u32 color, float shrinkRate) {
  DieParticle p;
  p.pos        = m_origin;
  p.vel        = direction;
  p.size       = startSize;
  p.rotation   = 0.0f;
  p.color      = color;
  p.shrinkRate = shrinkRate;
  m_particles.push_back(p);
}

DieEffect::DieEffect(float duration, Vec2 pos) : m_duration(duration), m_origin(pos) {
  Logger::debug("DieEffect::DieEffect init");

  const float speed = 20.0f;
  addParticle(Vec2(-2.0f, 1.4f).normalized() * speed, 10.0f, clrBlackSemi, 5.0f);
  addParticle(Vec2(0.0f, 1.6f).normalized() * speed, 12.0f, clrBlackSemi, 8.0f);
  addParticle(Vec2(2.0f, 1.4f).normalized() * speed, 8.0f, clrBlackSemi, 4.0f);
  addParticle(Vec2(-1.8f, -0.5f).normalized() * speed, 4.0f, clrBlackSemi, 2.0f);
}

bool DieEffect::update(float dt) {
  Logger::trace("DieEffect::update %.2f/%f", m_timer, m_duration);
  m_timer += dt;

  for (auto &p : m_particles) {
    p.pos += p.vel * dt;
    p.size -= p.shrinkRate * dt;
    p.rotation += 2.0f * dt;
    p.size = std::max(p.size, 0.0f);
  }

  auto removed = std::ranges::remove_if(m_particles, [](float size) { return size <= 0.0f; }, &DieParticle::size);
  m_particles.erase(removed.begin(), m_particles.end());

  return m_timer >= m_duration;
}

void DieEffect::draw(Renderer &renderer) {
  for (const auto &p : m_particles) {
    renderer.drawTriangle(p.pos, p.size, p.color);
  }
}
