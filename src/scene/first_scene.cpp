#include <memory>

#include "scene/first_scene.h"
#include "scene/game_scene.h"
#include "game/game.h"

FirstScene::FirstScene() {
  Image game_over_image = ImageText("SPACE\nINVADERS", 40, RED);
  titleTexture = LoadTextureFromImage(game_over_image);
  UnloadImage(game_over_image);
}

FirstScene::~FirstScene() {
  UnloadTexture(titleTexture);
}

void FirstScene::draw() const {
  ClearBackground(BLACK);
  DrawTexture(
    titleTexture,
    GetScreenWidth()/2 - titleTexture.width/2,
    GetScreenHeight()/2 - titleTexture.height/2,
    WHITE
  );
}

void FirstScene::update() {
  if(IsKeyPressed(KEY_ENTER)) {
    Game::Instance().getSceneManager().setCurrentScene(std::make_unique<GameScene>());
  }
}