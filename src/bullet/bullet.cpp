#include "bullet/bullet.h"


void Bullet::update() {
  if (!active) return;
  y -= speed;
  if (y < 0) active = false;
}

void Bullet::draw() const {
  if (!active) return;
  DrawRectangleRec(*this, RED);
}

void BulletArray::draw() const {
  for (const Bullet& b : *this) {
    b.draw();
  }
}

void BulletArray::update() {
  for (Bullet& b : *this) {
    b.update();
  }
}

Bullet* BulletArray::pickAvailableBullet() const {
  for (const Bullet& b : *this) {
    if (!b.active) return (Bullet *)&b;
  }
  return nullptr;
}