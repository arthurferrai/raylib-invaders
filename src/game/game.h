#ifndef __GAME_H_DEFINED__
#define __GAME_H_DEFINED__

#include <memory>
#include "scene/scene.h"
#include "scene_manager/scene_manager.h"

class Game {
public:
  ~Game();
  static Game& Instance();
  void start(std::unique_ptr<Scene> first_scene);
  void end() {running = false;};
  SceneManager& getSceneManager() const {return *sceneManager;};

private:
  bool running;
  std::unique_ptr<SceneManager> sceneManager;
  Game();
};

#endif