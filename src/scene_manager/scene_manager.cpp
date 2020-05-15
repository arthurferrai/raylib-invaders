#include <cassert>
#include "scene_manager/scene_manager.h"

Scene& SceneManager::getCurrentScene() const {
  assert(current_scene);
  return *current_scene;
}

void SceneManager::setCurrentScene(std::unique_ptr<Scene> new_scene) {
  assert(current_scene);
  current_scene->unload();
  current_scene = std::move(new_scene);
  current_scene->init();
}

SceneManager::SceneManager(std::unique_ptr<Scene> start_scene) {
  assert(start_scene);
  current_scene = std::move(start_scene);
  current_scene->init();
}