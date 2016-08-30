#ifndef __NODEMODEL_HPP__		
#define __NODEMODEL_HPP__

#include "base.h"
#include "node.hpp"
#include "model.hpp"
#include "camera.hpp"

namespace glRender
{

class NodeModel : public Node
{
public:
  NodeModel(Model * model);
  ~NodeModel();
  
  void update() override;
  void draw(Camera * camera) override;

  Model * model();

private:
  Model * m_model;

};

}

#endif /* __NODEMODEL_HPP__ */

