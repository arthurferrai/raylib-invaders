#ifndef __SCENE_MANAGER_H_DEFINED__
#define __SCENE_MANAGER_H_DEFINED__

#include "scene/scene.h"

class SceneManager {
public:

  static SceneManager& GetInstance();

  Scene*& getCurrentScene();
  void setCurrentScene(Scene*);

  // Disable all copy/move constructuctors
  SceneManager(const SceneManager&) = delete;
  SceneManager(SceneManager&&) = delete;
  SceneManager& operator=(const SceneManager&) = delete;
  SceneManager& operator=(SceneManager&&) = delete;

protected:
  SceneManager(){}

  Scene *current_scene;
};

#endif