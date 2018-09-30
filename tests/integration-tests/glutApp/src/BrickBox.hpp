#ifndef BRICKBOX_H
#define BRICKBOX_H

#include "glRender.h"

namespace glRender {

class BrickBox : public NodeMixedWith<IUpdateable, IDrawable>
{
public:
  BrickBox();
  ~BrickBox();

  void update() override;
  void draw(Camera * camera) override;

  Model * model();
  AABB * bb() const;

private:
  Model * m_model;
  AABB * m_aabb;

};

}

#endif // BRICKBOX_H
