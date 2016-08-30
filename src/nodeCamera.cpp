#include "nodeCamera.hpp"

namespace glRender {

NodeCamera::NodeCamera(Camera * camera) :
	m_camera(camera)
{

}

NodeCamera::~NodeCamera()
{

}

Camera * NodeCamera::camera()
{
	return m_camera;
}

}
