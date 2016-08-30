#include "perspectiveCamera.hpp"

namespace glRender {
PerspectiveCamera::PerspectiveCamera(float fieldOfView, float aspectRatio, float nearPlane, float farPlane) :
    Camera(),
    m_fieldOfView(fieldOfView),
    m_aspectRatio(aspectRatio),
    m_nearPlane(nearPlane),
    m_farPlane(farPlane)
{
    calculateProjectionMatrix();
}

void PerspectiveCamera::calculateProjectionMatrix()
{
    float f;
    f = 1.0 / tanf(m_fieldOfView / 2.0f);

    Mat4 projectionMatrix;
    projectionMatrix[0] = f / m_aspectRatio;
    projectionMatrix[1] = 0.0f;
    projectionMatrix[2] = 0.0f;
    projectionMatrix[3] = 0.0f;

    projectionMatrix[4] = 0.0f;
    projectionMatrix[5] = f;
    projectionMatrix[6] = 0.0f;
    projectionMatrix[7] = 0.0f;

    projectionMatrix[8] = 0.0f;
    projectionMatrix[9] = 0.0f;
    projectionMatrix[10] = (m_farPlane + m_nearPlane) / (m_nearPlane - m_farPlane);
    projectionMatrix[11] = -1.0f;

    projectionMatrix[12] = 0.0f;
    projectionMatrix[13] = 0.0f;
    projectionMatrix[14] = (2.0 * m_farPlane * m_nearPlane) / (m_nearPlane - m_farPlane);
    projectionMatrix[15] = 0.0f;

    m_projectionMatrix = projectionMatrix;

}

float PerspectiveCamera::fieldOfView() const
{
    return m_fieldOfView;
}

void PerspectiveCamera::setFieldOfView(float angle)
{
    m_fieldOfView = angle;
    calculateProjectionMatrix();
}

float PerspectiveCamera::aspectRatio() const
{
    return m_aspectRatio;
}

void PerspectiveCamera::setAspectRatio(float aspectRatio)
{
    m_aspectRatio = aspectRatio;
    calculateProjectionMatrix();
}

float PerspectiveCamera::nearPlane() const
{
    return m_nearPlane;
}
void PerspectiveCamera::setNearPlane(float nearPlane)
{
    m_nearPlane = nearPlane;
    calculateProjectionMatrix();
}

float PerspectiveCamera::farPlane() const
{
    return m_farPlane;
}
void PerspectiveCamera::setFarPlane(float farPlane)
{
    m_farPlane = farPlane;
    calculateProjectionMatrix();
}

}
