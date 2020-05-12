#ifndef __GAME_SCENE_H_DEFINED__
#define __GAME_SCENE_H_DEFINED__

#include "raylib.h"

#include "scene/scene.h"
#include "player/player.h"
#include "bullet/bullet.h"
#include "enemy/enemy.h"

class GameScene : public Scene {
  public:
  GameScene();
  ~GameScene();

  void draw() const override;
  void update() override;
  void init() override;

  private:

  void initEnemies();
  void initBullets();
  void updateBullets();
  void hitEnemy();
  void moveEnemiesDown();
  void updateEnemies();
  void playerShoot();
  void checkGameOver();

  bool isGameOver;

  enum EnemyMovementState {
    MOVING_LEFT=-1,
    MOVING_RIGHT=1,
    MOVING_DOWN=0
  } enemiesDirection;
  Player player;
  BulletArray playerBullets;
  EnemyArray enemies;
  Texture gameOverTexture;
  int aliveEnemiesCount;
};

#endif