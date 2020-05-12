/*******************************************************************************************
* attempt to make a space invaders
********************************************************************************************/
#include <stddef.h>

#include "raylib.h"
#include "scene/scene.h"
#include "scene/first_scene.h"
#include "scene_manager/scene_manager.h"

Scene *& current_scene = SceneManager::GetInstance().getCurrentScene();
bool game_running = true;


void endGame() {
  game_running = false;
}

void initGame() {
  const int screenWidth = 800;
  const int screenHeight = 450;

  InitWindow(screenWidth, screenHeight, "raylib invaders");
  SetTargetFPS(60);
  SceneManager::GetInstance().setCurrentScene(new FirstScene);
}

void cleanupGame() {
  CloseWindow();
}

int main()
{
  // Initialization
  //--------------------------------------------------------------------------------------
  initGame();
  //--------------------------------------------------------------------------------------

  // Main game loop
  while (!WindowShouldClose() || !game_running) {  // Detect window close button or ESC key
    if (current_scene != NULL) {
      current_scene->update();
    }
    // Draw
    //----------------------------------------------------------------------------------
    BeginDrawing();
      if (current_scene != NULL) {
        current_scene->draw();
      }
    EndDrawing();
    //----------------------------------------------------------------------------------
  }
  if (current_scene != NULL) {
    current_scene->unload();
    delete current_scene;
  }
  // De-Initialization
  //--------------------------------------------------------------------------------------
  cleanupGame();
  //--------------------------------------------------------------------------------------

  return 0;
}