#pragma once
#include "cmp_physics.h"
#include <ecm.h>

class EnemyTurretComponent : public Component {
protected:
  void fire() const;
  float _firetime;
  sf::Vector2f _offset;
  sf::Vector2f _direction;
  std::weak_ptr<Entity> _player;
  float _rotationCooldown;

public:
  void update(double dt) override;
  void render() override {}
  explicit EnemyTurretComponent(Entity* p);
  EnemyTurretComponent() = delete;
};
