#ifndef MARK_H
#define MARK_H

#include "glRender.h"

namespace glRender {


class Mark : public IIntersectable
{
public:
  Mark(float r, float g, float b, float size);
  ~Mark();

  void update() override;
  void draw(Camera * camera) override;
  bool intersects(const Ray * ray) const override;

  Model * model() const;
  IBoundingBox * bb() const override;

  void onIntersection(IIntersectable * o) override
  {
  }

  void onSelect(Ray * ray, Camera * camera) override;
  void onMove(Vec3 & toPosition) override;

  void changeColor();

private:
  Model * m_model;
  AABB * m_aabb;

  float m_r;
  float m_g;
  float m_b;

};

}

#endif // MARK_H
