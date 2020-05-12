#ifndef __SCENE_H_DEFINED__
#define __SCENE_H_DEFINED__
class Scene {
  public:
  virtual ~Scene() {};

  virtual void init() {};
  virtual void update() {};
  virtual void draw() const {};
  virtual void unload() {};

  protected:
  Scene() = default;
  Scene(const Scene&) = default;
  Scene(Scene&&) = default;
  Scene& operator= (const Scene&) = default;
  Scene& operator= (Scene&&) = default;
};
#endif