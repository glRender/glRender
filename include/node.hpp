#ifndef __NODE_HPP__		
#define __NODE_HPP__

#include "base.h"
#include "camera.hpp"

namespace glRender
{

class Node
{
public:
  Node();
  // ~Node();

  bool addChild(Node * node);
  std::vector<Node *> childs();
  Node * parent();

  void traverse(std::function<void(Node * node)> handler);
  
  virtual void update() = 0;
  virtual void draw(Camera * camera) = 0;

private:
  std::vector<Node * > m_childs;
  Node * m_parent;

};

}

#endif /* __NODE_HPP__ */
