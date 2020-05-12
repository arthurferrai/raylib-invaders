#ifndef __SCENE_MANAGER_H_DEFINED__
#define __SCENE_MANAGER_H_DEFINED__

#include "scene/scene.h"
#include <memory>

class SceneManager {
public:

  static SceneManager& GetInstance();

  const std::unique_ptr<Scene>& getCurrentScene() const;
  void setCurrentScene(Scene*);
  void setCurrentScene(std::unique_ptr<Scene>);

  // Disable all copy/move constructuctors
  SceneManager(const SceneManager&) = delete;
  SceneManager(SceneManager&&) = delete;
  SceneManager& operator=(const SceneManager&) = delete;
  SceneManager& operator=(SceneManager&&) = delete;

protected:
  SceneManager() : current_scene{nullptr} {}
  std::unique_ptr<Scene> current_scene;
};

#endif