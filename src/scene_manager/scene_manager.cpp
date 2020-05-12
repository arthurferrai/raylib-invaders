#include "scene_manager/scene_manager.h"

SceneManager& SceneManager::GetInstance() {
  static SceneManager instance;
  return instance;
}

const std::unique_ptr<Scene>& SceneManager::getCurrentScene() const {
  return current_scene;
}

void SceneManager::setCurrentScene(Scene* new_scene) {
  setCurrentScene(std::unique_ptr<Scene>(new_scene));
}

void SceneManager::setCurrentScene(std::unique_ptr<Scene> new_scene) {
  if (current_scene) current_scene->unload();
  current_scene = std::move(new_scene);
  current_scene->init();
}