#include "enemy/enemy.h"

void Enemy::draw() const {
  if (!alive) return;
  DrawRectangleRec(*this, ORANGE);
}

void EnemyArray::draw() const {
  for (auto it = begin(); it != end(); it++) {
    it->draw();
  }
}