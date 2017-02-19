#ifndef QUADRATICBEZEIRCURVE_H
#define QUADRATICBEZEIRCURVE_H

#include "glRender.h"

namespace glRender {

class QuadraticBezeirCurve : public Node
{
public:
  QuadraticBezeirCurve(Vec3 p0, Vec3 p1, Vec3 p2, uint segmentsNumber, float r, float g, float b);
  ~QuadraticBezeirCurve();

  void update() override;
  void draw(Camera * camera) override;

  Model * model() override;
  IBoundingBox * bb() override;

private:
  Model * m_model;
  AABB * m_aabb;

  Vec3 m_p0;
  Vec3 m_p1;
  Vec3 m_p2;

  int m_segmentsNumber;

  float m_r;
  float m_g;
  float m_b;

};

}


#endif // QUADRATICBEZEIRCURVE_H
