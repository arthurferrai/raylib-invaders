#include <cassert>
#include "raylib.h"

#include "game/game.h"


constexpr int SCREEN_WIDTH = 800;
constexpr int SCREEN_HEIGHT = 450;
constexpr auto SCREEN_TITLE = "Raylib Invaders";
constexpr int TARGET_FPS = 60;

Game& Game::Instance() {
  static Game instance;
  return instance;
}

Game::Game() : running{false}, sceneManager() {
  TraceLog(LOG_INFO, "Initializing raylib.");
  InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_TITLE);
  SetTargetFPS(TARGET_FPS);
}
Game::~Game() {
  CloseWindow();
}
void Game::start(std::unique_ptr<Scene> first_scene) {
  assert(!sceneManager);
  TraceLog(LOG_INFO, "Assigning first scene to SceneManager.");
  sceneManager = std::make_unique<SceneManager>(std::move(first_scene));

  running = true;
  TraceLog(LOG_INFO, "Everything set up, starting main loop.");
  try {
    while (running) {
      sceneManager->getCurrentScene().update();
      BeginDrawing();
      sceneManager->getCurrentScene().draw();
      EndDrawing();
      if(WindowShouldClose()) running = false;
    }
  }
  catch(const std::exception& e) {
    TraceLog(LOG_ERROR, "Exception on main loop.");
    TraceLog(LOG_ERROR, e.what());
    exit(EXIT_FAILURE);
  }

  TraceLog(LOG_INFO, "Main loop finished.");
  sceneManager->getCurrentScene().unload();
}