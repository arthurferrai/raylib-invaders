/*******************************************************************************************
* attempt to make a space invaders
********************************************************************************************/
#include <memory>
#include <cassert>

#include "raylib.h"
#include "scene/scene.h"
#include "scene/first_scene.h"
#include "scene_manager/scene_manager.h"

bool game_running = true;

void endGame() {
  game_running = false;
}

void initGame() {
  const int screenWidth = 800;
  const int screenHeight = 450;

  InitWindow(screenWidth, screenHeight, "raylib invaders");
  SetTargetFPS(60);
  SceneManager::GetInstance().setCurrentScene(std::make_unique<FirstScene>());
}

void cleanupGame() {
  CloseWindow();
}

int main() {
  initGame();
  // getting reference to current scene from scene manager
  const std::unique_ptr<Scene>& current_scene = SceneManager::GetInstance().getCurrentScene();
  assert(current_scene); // here we MUST have a scene
  // Main game loop
  while (!WindowShouldClose() || !game_running) {  // Detect window close button or ESC key
    current_scene->update();
    BeginDrawing();
    current_scene->draw();
    EndDrawing();
  }
  current_scene->unload();
  cleanupGame();

  return 0;
}