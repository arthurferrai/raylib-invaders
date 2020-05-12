#ifndef __ENEMY_H_DEFINED__
#define __ENEMY_H_DEFINED__

#include <vector>
#include "raylib.h"

class Enemy : public Rectangle {
  public:
  Enemy(float width, float height) :
    Rectangle{.x=0, .y=0, .width=width, .height=height},
    alive{false} {}

  void draw() const;
  bool alive;
};

class EnemyArray : private std::vector<Enemy>{
  public:
  EnemyArray(int size, const Enemy& src) : vector<Enemy>(size, src) {};
  using vector<Enemy>::begin;
  using vector<Enemy>::end;
  using vector<Enemy>::iterator;

  Enemy& operator[] (int i) {return vector<Enemy>::at(i);};
  const Enemy& operator[] (int i) const {return vector<Enemy>::at(i);};

  void draw() const;
};


#endif