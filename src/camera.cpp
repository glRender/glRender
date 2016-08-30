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

    Mat4 viewMatrix;
    viewMatrix[0] = X.x;
    viewMatrix[4] = X.y;
    viewMatrix[8] = X.z;
    viewMatrix[12] = -X.dot(position);

    viewMatrix[1] = Y.x;
    viewMatrix[5] = Y.y;
    viewMatrix[9] = Y.z;
    viewMatrix[13] = -Y.dot(position);

    viewMatrix[2] = Z.x;
    viewMatrix[6] = Z.y;
    viewMatrix[10] = Z.z;
    viewMatrix[14] =  -Z.dot(position);

    viewMatrix[3] = 0;
    viewMatrix[7] = 0;
    viewMatrix[11] = 0;
    viewMatrix[15] = 1.0f;

    setTransformationMatrix(viewMatrix);

}

const Mat4& Camera::projectionMatrix() const
{
	return m_projectionMatrix;
}

void Camera::setProjectionMatrix(const Mat4& matrix)
{
	m_projectionMatrix = matrix;
}

const Mat4& Camera::transformationMatrix() const
{
    return m_transformationMatrix;
}

void Camera::translate(const float x, const float y, const float z)
{
    Vec3 transformedValue = Positionable::transformationMatrix() * Vec3(x,y,z);
    Positionable::translate(transformedValue.x, transformedValue.y, transformedValue.z);

    m_transformationMatrix = m_transformationMatrix.translate(-x,-y,-z);

}

void Camera::translate(const Vec3 & value)
{
    translate(value.x, value.y, value.z);
}

void Camera::rotate(const float value, const float x, const float y, const float z)
{
    Vec3 pos = position();
    Positionable::translate( -pos );
    Positionable::rotate( -value, x, y, z );
    Positionable::translate( pos );

    m_transformationMatrix = m_transformationMatrix.rotate( value, x, y, z );
}

void Camera::rotate(const float value, const Vec3 & v)
{
    rotate( value, v.x, v.y, v.z );
}

}
