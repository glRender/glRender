#include "cameraControlNode.hpp"

#include "geometry.hpp"
#include "texture.hpp"
#include "textures.hpp"
#include "geometryHelper.hpp"
#include "shaderProgram.hpp"
#include "vec3.hpp"
#include "model.hpp"

using namespace glRender;

glRender::CameraControlNode::CameraControlNode(glRender::Camera *camera) :
    m_camera(camera)
{
    std::shared_ptr<Geometry> geometry = GeometryHelper::Arrows();
    Textures * textures = new Textures();
    std::shared_ptr<ShaderProgram> shaderProgram = ResourceManager::instance().shaderPrograms().get("coloredShP");

    shaderProgram->addAttribute<Vec3>("vertex");

    shaderProgram->addUniform<Mat4>("projection");
    shaderProgram->addUniform<Mat4>("view");
    shaderProgram->addUniform<Mat4>("model");
    shaderProgram->addUniform<Vec3>("color");

    m_model = new Model(geometry, textures, shaderProgram);
    m_model->setWireframeMode(true);
    Mat4 l = m_model->localMatrix();
    m_model->setLocalMatrix(l.scale(0.005f));
    m_model->setOrigin(0.5f, 0.25f, -2.0f);
}

void glRender::CameraControlNode::draw(glRender::Camera *camera)
{
    m_model->draw(camera);
}

void glRender::CameraControlNode::onKeyPress(KeyboardKey key)
{
    switch(key)
    {
    case IKeyPressable::KeyboardKey::W: {
        m_camera->setPosition(m_camera->position() + m_camera->front() * cameraMoveSpeed );
        m_model->setOrigin(m_model->origin() + m_camera->front() * cameraMoveSpeed);
    }; break;

    case IKeyPressable::KeyboardKey::S: {
        m_camera->setPosition(m_camera->position() - m_camera->front() * cameraMoveSpeed);
        m_model->setOrigin(m_model->origin() - m_camera->front() * cameraMoveSpeed);
    }; break;

    case IKeyPressable::KeyboardKey::A: {
        m_camera->setPosition(m_camera->position() - m_camera->right() * cameraMoveSpeed );
        m_model->setOrigin(m_model->origin() - m_camera->right() * cameraMoveSpeed);
    }; break;

    case IKeyPressable::KeyboardKey::D: {
        m_camera->setPosition(m_camera->position() + m_camera->right() * cameraMoveSpeed );
        m_model->setOrigin(m_model->origin() + m_camera->right() * cameraMoveSpeed);
    }; break;

    case IKeyPressable::KeyboardKey::Q: {
        m_camera->setEulerAngles( m_camera->pitch(), m_camera->yaw() + cameraRotationSpeed, m_camera->roll() );
    }; break;

    case IKeyPressable::KeyboardKey::E: {
        m_camera->setEulerAngles( m_camera->pitch(), m_camera->yaw() - cameraRotationSpeed, m_camera->roll() );
    }; break;

    case IKeyPressable::KeyboardKey::Z: {
        m_camera->setPosition(m_camera->position() + m_camera->up() * cameraMoveSpeed );
        m_model->setOrigin(m_model->origin() + m_camera->up() * cameraMoveSpeed);
    }; break;

    case IKeyPressable::KeyboardKey::X: {
        m_camera->setPosition(m_camera->position() - m_camera->up() * cameraMoveSpeed );
        m_model->setOrigin(m_model->origin() - m_camera->up() * cameraMoveSpeed);
    }; break;

    case IKeyPressable::KeyboardKey::R: {
        m_camera->setEulerAngles( m_camera->pitch() + cameraRotationSpeed, m_camera->yaw(), m_camera->roll() );
    }; break;

    case IKeyPressable::KeyboardKey::F: {
        m_camera->setEulerAngles( m_camera->pitch() - cameraRotationSpeed, m_camera->yaw(), m_camera->roll() );
    }; break;

    default: {

    }

    }
}
