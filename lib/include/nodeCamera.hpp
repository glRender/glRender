#ifndef __NODECAMERA_HPP__		
#define __NODECAMERA_HPP__

#include "base.h"
#include "node.hpp"
#include "camera.hpp"

namespace glRender
{

class NodeCamera : public Node
{
public:
  NodeCamera(Camera * camera);
  ~NodeCamera();

  Camera * camera();

private:
  Camera * m_camera;

};

}

#endif /* __NODECAMERA_HPP__ */
