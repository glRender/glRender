#ifndef MARK_H
#define MARK_H

#include "glRender.h"

namespace glRender {


class Mark : public IIntersectable
{
public:
  Mark(Vec3 color, float size, uint i, uint j, uint k);
  ~Mark();

  void update() override;
  void draw(CameraPtr camera) override;
  bool intersects(const RayPtr ray) const override;

  Model * model() const;
  IBoundingBox * bb() const override;

  void onIntersection(IIntersectable * o) override
  {
  }

  void onMouseUp(RayPtr ray, CameraPtr camera) override;
  void onMouseDown(RayPtr ray, CameraPtr camera) override;
  void onMouseMove(Vec3 & toPosition) override;

  void changeColor();

private:
  Model * m_model;
  AABB * m_aabb;

  Vec3 m_color;

  uint m_i;
  uint m_j;
  uint m_k;

  bool m_isSelected = false;

};

}

#endif // MARK_H
