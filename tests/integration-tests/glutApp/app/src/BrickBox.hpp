#ifndef BRICKBOX_H
#define BRICKBOX_H

#include "glRender.h"

namespace glRender {

class BrickBox : public Node
{
public:
  BrickBox();
  ~BrickBox();

  void update() override;
  void draw(Camera * camera) override;

  Model * model() override;
  AABB * bb() override;

private:
  Model * m_model;
  AABB * m_aabb;

};

}

#endif // BRICKBOX_H
