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
  virtual ~Node();

  bool addChild(Node * node);
  std::vector<Node *> childs();
  Node * parent();

  void traverse(std::function<void(Node * node)> handler);
  std::vector<Node *> query(std::function<bool(const Node * node)> condition);

  virtual void update() = 0;
  virtual void draw(Camera * camera) = 0;
  virtual Model * model() = 0;
  virtual IBoundingBox * bb() const = 0;
  virtual void setOrigin(const Vec3 & pos);
  void setOrigin(float x, float y, float z);
  void setSelectable(bool isSelectable);
  bool isSelectable() const;

private:
  std::vector<Node * > m_childs;
  Node * m_parent;
  bool m_isSelectable = false;

};

}

#endif /* __NODE_HPP__ */
