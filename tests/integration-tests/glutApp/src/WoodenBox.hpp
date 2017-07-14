#ifndef WOODENBOX_H
#define WOODENBOX_H

#include "glRender.h"

namespace glRender {

class WoodenBox : public NodeMixedWith<IUpdateable, IDrawable>
{
public:
  WoodenBox();
  ~WoodenBox();

  void update() override;
  void draw(Camera * camera) override;
std::shared_ptr<ShaderProgram> shaderProgram;

  Model * model()/* override*/;
  IBoundingBox * bb() const/* override*/;

private:
  Model * m_model;
  AABB * m_aabb;

};

}

#endif // WOODENBOX_H
