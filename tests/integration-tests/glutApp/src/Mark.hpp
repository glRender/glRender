#ifndef MARK_H
#define MARK_H

#include "glRender.h"

namespace glRender {

class AABBNodeVisualizator;

class Mark : public NodeMixedWith<IUpdateable, IDrawable, IIntersectable>
{
public:
  Mark(Vec3 color, float size, uint i, uint j, uint k);
  ~Mark();

  void update() override;
  void draw(Camera * camera) override;
  bool intersects(const RayPtr ray) const override;

  const Model * model() const;
  const IBoundingBox * bb() const override;
  void setOrigin(const Vec3 & origin);

//  void onIntersection(IIntersectable * o) override
//  {
//  }

  void onMouseUp(Vec3 & position, RayPtr ray, Camera * camera) override;
  void onMouseDown(Vec3 & position, RayPtr ray, Camera * camera) override;
  void onMouseMove(Vec3 & toPosition) override;

  void changeColor();

private:
  Model * m_model;
  AABB * m_aabb;
  AABBNodeVisualizator * m_aabbVisualizator;

  Vec3 m_color;

  uint m_i;
  uint m_j;
  uint m_k;

  bool m_isSelected = false;

};

}

#endif // MARK_H
