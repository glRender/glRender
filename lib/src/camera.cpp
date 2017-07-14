#include "camera.hpp"

namespace glRender {

Camera::Camera(float nearPlane, float farPlane)
    : m_nearPlane(nearPlane)
    , m_farPlane(farPlane)
{
}

void Camera::lookAt(const Vec3 & position, const Vec3 & target, const Vec3 & up)
{
    Vec3 Y = up;
    Y.normalize();

    Vec3 Z = position - target;
    Z.normalize();

    Vec3 X = Y.cross(Z);
    Y = Z.cross(X);
    Y.normalize();

    X.normalize();

    Mat4 view;
    view.setRow(0, Vec4(X.x, X.y, X.z, -X.dot(position)));
    view.setRow(1, Vec4(Y.x, Y.y, Y.z, -Y.dot(position)));
    view.setRow(2, Vec4(Z.x, Z.y, Z.z, -Z.dot(position)));
    view.setRow(3, Vec4(0.0f, 0.0f, 0.0f, 1.0f));

    setLocalMatrix(view);

    m_position = position;
    m_target = target;
    m_direction = target - position;

    m_front = (target - position).normalize();
    m_right = m_front.cross(up);
    m_up = up;

}



//const Mat4 & Camera::transformationMatrix() const
//{
//    return m_transformationMatrix;
//}

const Vec3 & Camera::position() const
{
    return m_position;
}

const Vec3 & Camera::target() const
{
    return m_target;
}

const Vec3 & Camera::front() const
{
    return m_front;
}

const Vec3 & Camera::right() const
{
    return m_right;
}

const Vec3 & Camera::up() const
{
    return m_up;
}

float Camera::nearPlane() const
{
    return m_nearPlane;
}
void Camera::setNearPlane(float nearPlane)
{
    m_nearPlane = nearPlane;
    calculateProjectionMatrix();
}

float Camera::farPlane() const
{
    return m_farPlane;
}

void Camera::setFarPlane(float farPlane)
{
    m_farPlane = farPlane;
    calculateProjectionMatrix();
}

void Camera::shift(const Vec3 v)
{
    Vec3 newPos = position() + v;
    Vec3 newTarget = newPos + front();
    Vec3 newUp = up();

    lookAt(newPos, newTarget, newUp);
}

void Camera::setPosition(const Vec3 &pos)
{
    Vec3 newPos = pos;
    Vec3 newTarget = pos + front();
    Vec3 newUp = up();

    lookAt(newPos, newTarget, newUp);
}

void Camera::setTarget(const Vec3 &target)
{
    Vec3 newPos = position();
    Vec3 newTarget = target;
    Vec3 newUp = up();

    lookAt(newPos, newTarget, newUp);
}

void Camera::setDirection(const Vec3 &direction)
{
    Vec3 d = direction;
    d.normalize();

    Vec3 newPos = position();
    Vec3 newTarget = position() + d;
    Vec3 newUp = up();

    lookAt(newPos, newTarget, newUp);
}

void Camera::setEulerAngles(float pitch, float yaw, float roll)
{
    Mat4 m;
    m.rotate(pitch, Vec3::AXE_X());
    m.rotate(yaw,   Vec3::AXE_Y());
    m.rotate(roll,  Vec3::AXE_Z());

    Vec3 newPos = position();

    Vec3 newTarget = -Vec3::AXE_Z();
    Vec4 tmp(newTarget.x, newTarget.y, newTarget.z, 1.0f);
    tmp = m * tmp;
    newTarget.set(tmp.x, tmp.y, tmp.z);
    newTarget += position();

    Vec3 newUp = Vec3::AXE_Y();
    tmp.set(newUp.x, newUp.y, newUp.z, 1.0f);
    tmp = m * tmp;
    newUp.set(tmp.x, tmp.y, tmp.z);

    lookAt(newPos, newTarget, newUp);

    m_pitch = pitch;
    m_yaw = yaw;
    m_roll = roll;
}

void Camera::setLocalMatrix(const Mat4 & m)
{
    m_localMatrix = m;
    m_globalMatrix = m_localMatrix * m_parentsMatrix;
}

void Camera::setParentsMatrix(const Mat4 &m)
{
    m_parentsMatrix = m;
    m_globalMatrix = m_localMatrix * m_parentsMatrix;
}

void Camera::setGlobalMatrix(const Mat4 & m)
{
    m_globalMatrix = m;
}

const Mat4 &Camera::localMatrix() const
{
    return m_localMatrix;
}

const Mat4 &Camera::parentsMatrix() const
{
    return m_parentsMatrix;
}

float Camera::pitch() const
{
    return m_pitch;
}

float Camera::yaw() const
{
    return m_yaw;
}

float Camera::roll() const
{
    return m_roll;
}

}
