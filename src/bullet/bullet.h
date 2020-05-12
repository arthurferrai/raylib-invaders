#ifndef __BULLET_H_DEFINED__
#define __BULLET_H_DEFINED__

#include <vector>
#include "raylib.h"

class Bullet : public Rectangle {
  public:
  Bullet(float width, float height, float speed) :
   Rectangle{.x=0, .y=0, .width=width, .height=height},
   active{false},
   speed{speed} {};

  void update();
  void draw() const;

  bool active;

  private:
  float speed;
};

class BulletArray : private std::vector<Bullet> {
  public:
  BulletArray(int size, const Bullet& src) : vector<Bullet>(size, src) {};
  using vector<Bullet>::begin;
  using vector<Bullet>::end;
  using vector<Bullet>::iterator;

  Bullet& operator[] (int i) {return vector<Bullet>::at(i);};
  const Bullet& operator[] (int i) const {return vector<Bullet>::at(i);};
  Bullet* pickAvailableBullet() const;
  void update();
  void draw() const;
};


#endif