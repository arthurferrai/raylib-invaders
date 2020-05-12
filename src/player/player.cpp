#include "player/player.h"

template<class T>
const T& clamp( const T& v, const T& lo, const T& hi ) {
    return (v < lo) ? lo : (hi < v) ? hi : v;
}

void Player::move() {
  if (IsKeyDown(KEY_RIGHT)) x += speed;
  if (IsKeyDown(KEY_LEFT)) x -= speed;
  x = clamp(x, .0f, GetScreenWidth() - width);
}

void Player::draw() const {
  DrawRectangleRec(*this, GREEN);
  const float canonWidth = width / 5;
  const float canonHeight = height * 0.6;
  DrawRectangleRec(
    Rectangle{
      .x = x + (width/2) - (canonWidth/2),
      .y = y - canonHeight,
      .width = canonWidth,
      .height = canonHeight
    },
    GREEN
  );
}

const Vector2 Player::getCanonPosition() const {
  const float canonHeight = height * 0.6;
  return Vector2{
    .x=x + (width / 2),
    .y=y - canonHeight
  };
}