#include <memory>

#include "scene/game_scene.h"
#include "scene/first_scene.h"
#include "scene_manager/scene_manager.h"

const float PLAYER_WIDTH = 40;
const float PLAYER_HEIGHT = 15;
const float PLAYER_SPEED = 5;

const unsigned int NUM_BULLETS = 4;

const float BULLET_WIDTH = 5;
const float BULLET_HEIGHT = 15;
const float BULLET_SPEED = 5;

const int NUM_ENEMIES = 50;
const float ENEMY_WIDTH = 30;
const float ENEMY_HEIGHT = 30;

const int NUM_ROWS = 5;
const int ENEMY_SPEED = 1;

const int enemiesPerRow = NUM_ENEMIES / NUM_ROWS;

GameScene::GameScene() :
  isGameOver{false},
  enemiesDirection{MOVING_RIGHT},
  player{PLAYER_WIDTH, PLAYER_HEIGHT, PLAYER_SPEED},
  playerBullets{NUM_BULLETS, Bullet(BULLET_WIDTH, BULLET_HEIGHT, BULLET_SPEED)},
  enemies{NUM_ENEMIES, Enemy(ENEMY_WIDTH, ENEMY_HEIGHT)},
  aliveEnemiesCount{NUM_ENEMIES}
{
  Image gameOverImage = ImageText("GAME OVER", 40, RED);
  gameOverTexture = LoadTextureFromImage(gameOverImage);
  UnloadImage(gameOverImage);
}

GameScene::~GameScene() {
  UnloadTexture(gameOverTexture);
}

void GameScene::initEnemies() {
  const int distanceBetweenEnemies = GetScreenWidth() / (enemiesPerRow + 1);
  for (int i = 0; i < NUM_ENEMIES; i++) {
    const int currentLine = i / enemiesPerRow;
    const int currentCol = i % enemiesPerRow;
    Enemy &e = enemies[i];
    e.alive = true;
    e.x = currentCol * distanceBetweenEnemies;
    e.y = (currentLine * e.height) + (currentLine * (e.height / 2));
  }
  aliveEnemiesCount = NUM_ENEMIES;
}

void GameScene::initBullets() {
  for(auto &b : playerBullets) {
    b.active = false;
  }
}

void GameScene::init() {
  initEnemies();
  initBullets();
  isGameOver = false;
}

void GameScene::updateBullets() {
  for (Bullet &b : playerBullets) {
    if (!b.active) continue;
    b.update();
  }
}

void GameScene::hitEnemy() {
  for (Bullet &b : playerBullets) {
    if (!b.active) continue;
    for (Enemy &e : enemies) {
      if (!e.alive) continue;
      if (CheckCollisionRecs(b, e)) {
        b.active = false;
        e.alive = false;
        aliveEnemiesCount--;
        break;
      }
    }
  }
}

void GameScene::moveEnemiesDown() {
  for (Enemy &e : enemies) {
    if (!e.alive) continue;
    e.y += e.height;
  }
  enemiesDirection = enemiesDirection == MOVING_LEFT ? MOVING_RIGHT : MOVING_LEFT;
}

void GameScene::updateEnemies() {
  if (enemiesDirection == MOVING_RIGHT) {
    const int screenWidth = GetScreenWidth();
    for (int j = 1; j <= enemiesPerRow; j++) {
      for (int i = enemiesPerRow - j; i < NUM_ENEMIES; i += enemiesPerRow) {
        Enemy &e = enemies[i];
        if (!e.alive) continue;
        if (e.x + e.width >= screenWidth) {
          moveEnemiesDown();
          return;
        }
      }
    }
  } else {
    for (int j = 0; j < enemiesPerRow; j++) {
      for (int i = j; i < NUM_ENEMIES; i += enemiesPerRow) {
        Enemy &e = enemies[i];
        if (!e.alive) continue;
        if (e.x <= 0) {
          moveEnemiesDown();
          return;
        }
      }
    }
  }
  for (Enemy &e : enemies) {
    e.x += ENEMY_SPEED * enemiesDirection;
  }
}

void GameScene::playerShoot() {
  if (!IsKeyPressed(KEY_SPACE)) return;

  Bullet *b = playerBullets.pickAvailableBullet();
  if (!b) return;

  Vector2 canonPosition = player.getCanonPosition();
  b->x = canonPosition.x - (b->width / 2);
  b->y = canonPosition.y - b->height;
  b->active = true;
}

void GameScene::checkGameOver() {
  for (Enemy &e : enemies) {
    if (CheckCollisionRecs(e, player)) {
      isGameOver = true;
      return;
    }
  }
}

void GameScene::update() {
  if (!isGameOver) {
    player.move();
    playerShoot();
    updateBullets();
    hitEnemy();
    updateEnemies();
    checkGameOver();
  } else if (IsKeyPressed(KEY_ENTER)) {
    SceneManager::GetInstance().setCurrentScene(std::make_unique<FirstScene>());
  }
  #ifdef DEBUG
  if (IsKeyPressed(KEY_R)) init();
  if (IsKeyPressed(KEY_Q)) isGameOver = true;
  #endif
}

void GameScene::draw() const {
  ClearBackground(BLACK);
  player.draw();
  playerBullets.draw();
  enemies.draw();
  if (isGameOver)
    DrawTexture(
      gameOverTexture,
      GetScreenWidth() / 2 - gameOverTexture.width / 2,
      GetScreenHeight() / 2 - gameOverTexture.height / 2,
      WHITE
    );
  DrawFPS(10, 10);
}