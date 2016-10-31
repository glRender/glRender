#ifndef __NODE_HPP__		
#define __NODE_HPP__

#include "base.h"

#include "camera.hpp"
#include "boundingBox.hpp"
#include "model.hpp"

namespace glRender
{

class Node
{
public:
  ~Node();

  bool addChild(Node * node);
  std::vector<Node *> childs();
  Node * parent();

  void traverse(std::function<void(Node * node)> handler);
  
  virtual void update() = 0;
  virtual void draw(Camera * camera) = 0;
  virtual Model * model() = 0;
  virtual IBoundingBox * bb() = 0;
  virtual void setPosition(const Vec3 & pos);
  void setPosition(float x, float y, float z);
  void setSelectable(bool isSelectable);
  bool isSelectable();

private:
  std::vector<Node * > m_childs;
  Node * m_parent;
  bool m_isSelectable = false;

};

}

#endif /* __NODE_HPP__ */
