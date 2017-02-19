#pragma once

#include "glRender.h"

namespace glRender {

class Line : public Node
{
public:
  Line(Vec3 p0, Vec3 p1, uint segmentsNumber, float r, float g, float b);
  ~Line();

  void update() override;
  void draw(Camera * camera) override;

  Model * model() override;
  IBoundingBox * bb() override;

private:
  Model * m_model;
  AABB * m_aabb;

  Vec3 m_p0;
  Vec3 m_p1;

  int m_segmentsNumber;

  float m_r;
  float m_g;
  float m_b;
};

}
