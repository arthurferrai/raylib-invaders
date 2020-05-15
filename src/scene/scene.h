#ifndef __SCENE_H_DEFINED__
#define __SCENE_H_DEFINED__
class Scene {
  public:
  Scene() {}
  virtual ~Scene() {};

  virtual void init() {};
  virtual void update() {};
  virtual void draw() const = 0;
  virtual void unload() {};
};
#endif