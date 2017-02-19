#ifndef WOODENBOX_H
#define WOODENBOX_H

#include "glRender.h"

namespace glRender {

class WoodenBox : public Node
{
public:
  WoodenBox();
  ~WoodenBox();

  void update() override;
  void draw(Camera * camera) override;

  Model * model() override;
  IBoundingBox * bb() override;

private:
  Model * m_model;
  AABB * m_aabb;

};

}

#endif // WOODENBOX_H
