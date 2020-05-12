#include "scene_manager/scene_manager.h"

SceneManager& SceneManager::GetInstance() {
  static SceneManager instance;
  return instance;
}

Scene*& SceneManager::getCurrentScene() {
  return current_scene;
}

void SceneManager::setCurrentScene(Scene* new_scene) {
  if (current_scene) {
    current_scene->unload();
    delete current_scene;
  }
  current_scene = new_scene;
  current_scene->init();
}