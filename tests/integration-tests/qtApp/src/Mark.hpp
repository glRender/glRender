#ifndef MARK_H
#define MARK_H

#include <QDebug>

#include "glRender.h"

namespace glRender {

class Mark : public NodeMixedWith<IUpdateable, IDrawable, IIntersectable>
{
public:
  Mark(Vec3 color, float size, uint i, uint j, uint k);
  ~Mark();

  void update() override;
  void draw(Camera * camera) override;
  bool intersects(const RayPtr ray) const override;

  Model * model() const;
  IBoundingBox * bb() const override;

  void onMouseUp(Vec3 & position, RayPtr ray, Camera * camera) override;
  void onMouseDown(Vec3 & position, RayPtr ray, Camera * camera) override;
  void onMouseMove(Vec3 & toPosition) override;

  void changeColor();

private:
  Model * m_model;
  AABB * m_aabb;
  // AABBNodeVisualizator * m_aabbVisualizator;

  Vec3 m_color;
  bool m_isSelected = false;

};

class CameraNode : public NodeMixedWith<IUpdateable, IKeyPressable, IMouseListenable>
{
public:
    CameraNode(Camera * camera)
        : m_camera(camera)
        , m_front(camera->front())
    {
    }

    void update() override
    {
    }

    void onMouseUp(Vec2 normDeviceCoords, RayPtr ray, Camera *) override
    {
        qDebug() << Q_FUNC_INFO;

    }

    void onMouseDown(Vec2 normDeviceCoords, RayPtr ray, Camera *) override
    {
        qDebug() << Q_FUNC_INFO;
        lastPoint = normDeviceCoords;
    }

    void onMouseMove(Vec2 normDeviceCoords, RayPtr ray, Camera *) override
    {
        qDebug() << Q_FUNC_INFO;
//        std::cout << "ray dir" << ray->dir().toStdString();
//        std::cout << m_front << std::endl;
//        m_front = ray->dir();
//        std::cout << m_front << std::endl;
        float xoffset = normDeviceCoords.x - lastPoint.x;
        float yoffset = normDeviceCoords.y - lastPoint.y;

        float sensitivity = 0.5f;
        xoffset *= sensitivity;
        yoffset *= sensitivity;
        qDebug() << "before" << xoffset << yaw;

        yaw += xoffset;
//        yaw = abs((uint)yaw % 360);

//        qDebug() << xoffset << yoffset;

        pitch += yoffset;

        if(pitch > 89.0f)
            pitch = 89.0f;
        if(pitch < -89.0f)
            pitch = -89.0f;


        qDebug() << "after" << xoffset << yaw;

//        Vec3 front;
//        front.x = cos(MATH_DEG_TO_RAD(yaw)) * cos(MATH_DEG_TO_RAD(pitch));
//        front.y = sin(MATH_DEG_TO_RAD(pitch));
//        front.z = sin(MATH_DEG_TO_RAD(yaw)) * cos(MATH_DEG_TO_RAD(pitch));
//        m_front = front.normalize();

//        m_camera->setPosition( m_front );
        m_camera->setEulerAngles(pitch, yaw, m_camera->roll() );

    }

    void onKeyPress(KeyboardKey key) override
    {
        switch(key)
        {
        case IKeyPressable::KeyboardKey::W: {

            m_camera->setPosition( m_camera->position() + m_camera->front() * cameraMoveSpeed );
        }; break;

        case IKeyPressable::KeyboardKey::S: {
            m_camera->setPosition( m_camera->position() - m_camera->front() * cameraMoveSpeed );
        }; break;

        case IKeyPressable::KeyboardKey::A: {
            m_camera->setPosition( m_camera->position() - m_camera->right() * cameraMoveSpeed );
        }; break;

        case IKeyPressable::KeyboardKey::D: {
            m_camera->setPosition( m_camera->position() + m_camera->right() * cameraMoveSpeed );
        }; break;

        case IKeyPressable::KeyboardKey::Q: {
            m_camera->setEulerAngles( m_camera->pitch(), m_camera->yaw() + cameraRotationSpeed, m_camera->roll() );
        }; break;

        case IKeyPressable::KeyboardKey::E: {
            m_camera->setEulerAngles( m_camera->pitch(), m_camera->yaw() - cameraRotationSpeed, m_camera->roll() );
        }; break;

        case IKeyPressable::KeyboardKey::Z: {
            m_camera->setPosition( m_camera->position() + m_camera->up() * cameraMoveSpeed );
        }; break;

        case IKeyPressable::KeyboardKey::X: {
            m_camera->setPosition( m_camera->position() - m_camera->up() * cameraMoveSpeed );
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

private:
    CameraPtr m_camera;
    Vec3 m_front;
    Vec2 lastPoint;
    float yaw = 0;
    float pitch = 0;
    float cameraMoveSpeed = 0.3f;
    float cameraRotationSpeed = 5.0f;

};


}

#endif // MARK_H
