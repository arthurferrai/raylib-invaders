#ifndef __SCENE_MANAGER_H_DEFINED__
#define __SCENE_MANAGER_H_DEFINED__

#include "scene/scene.h"
#include <memory>

class SceneManager {
public:
  SceneManager(std::unique_ptr<Scene> start_scene);

  Scene& getCurrentScene() const;
  void setCurrentScene(std::unique_ptr<Scene>);
private:
  std::unique_ptr<Scene> current_scene;
};

#endif