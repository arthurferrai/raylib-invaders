#ifndef __PLAYER_H_DEFINED__
#define __PLAYER_H_DEFINED__

#include "raylib.h"

class Player : public Rectangle {
  public:
  Player(float width, float height, float speed) :
    Rectangle{
      .x=0,
      .y=GetScreenHeight() - height,
      .height=height,
      .width=width
    },
    speed{speed} {};

  void move();
  void draw() const;
  const Vector2 getCanonPosition() const;

  private:
  float speed;
};

#endif