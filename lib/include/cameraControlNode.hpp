#pragma once

#include "base.h"
#include "nodeMixer.hpp"
#include "resourceManager.hpp"

namespace glRender
{

class Textures;
class Geometry;
class ShaderProgram;

class CameraControlNode : public NodeMixedWith<IDrawable, IKeyPressable>
{
public:
    CameraControlNode(Camera * camera);
    void draw(Camera * camera) override;
    void onKeyPress(KeyboardKey key) override;

private:
    float cameraMoveSpeed = 0.3f;
    float cameraRotationSpeed = 5.0f;
    Camera * m_camera;
    Model * m_model;
};

}
