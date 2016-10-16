#include "camera.hpp"

namespace glRender {

Camera::Camera()
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
//    view[0] = X.x;
//    view[4] = X.y;
//    view[8] = X.z;
//    view[12] = -X.dot(position);

//    view[1] = Y.x;
//    view[5] = Y.y;
//    view[9] = Y.z;
    view.setRow(1, Vec4(Y.x, Y.y, Y.z, -Y.dot(position)));
//    view[13] = -Y.dot(position);

//    view[2] = Z.x;
//    view[6] = Z.y;
//    view[10] = Z.z;
    view.setRow(2, Vec4(Z.x, Z.y, Z.z, -Z.dot(position)));
//    view[14] =  -Z.dot(position);

//    view.setColumn(3, Vec3(-X.dot(position), -Y.dot(position), -Z.dot(position)));

    view.setRow(3, Vec4(0.0f, 0.0f, 0.0f, 1.0f));

//    view[3] = 0;
//    view[7] = 0;
//    view[11] = 0;
//    view[15] = 1.0f;

    m_transformationMatrix = view;

    m_position = position;
    m_target = target;
    m_up = up;

}

const Mat4 & Camera::projectionMatrix() const
{
	return m_projectionMatrix;
}

const Mat4 & Camera::transformationMatrix() const
{
    return m_transformationMatrix;
}

const Vec3 & Camera::position() const
{
    return m_position;
}

const Vec3 & Camera::target() const
{
    return m_target;
}

const Vec3 Camera::normalizedDirection() const
{
    Vec3 normalizedDir = target() - position();
    normalizedDir.normalize();
    return normalizedDir;
}

const Vec3 Camera::front() const
{
    return normalizedDirection();
}

const Vec3 Camera::right() const
{
    Vec3 normDir = normalizedDirection();
    return normDir.cross(up());
}

const Vec3 & Camera::up() const
{
    return m_up;
}

void Camera::shift(const Vec3 v)
{
    Vec3 newPos = position() + v;
    Vec3 newTarget = newPos + normalizedDirection();
    Vec3 newUp = up();

    lookAt(newPos, newTarget, newUp);
}

}
