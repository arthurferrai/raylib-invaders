#ifndef __FIRST_SCENE_H_DEFINED__
#define __FIRST_SCENE_H_DEFINED__

#include "scene/scene.h"
#include "raylib.h"

class FirstScene : public Scene {
  public:
  FirstScene();
  ~FirstScene();

  void draw() const override;
  void update() override;
  private:
  Texture titleTexture;
};

#endif