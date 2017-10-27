#include "orthographicCamera.hpp"

#include "camera.hpp"

using namespace glRender;

OrthographicCamera::OrthographicCamera(float width, float ratio, float nearPlane, float farPlane)
    : Camera(nearPlane, farPlane)
    , m_width(width)
    , m_aspectRatio(ratio)
{
    calculateP0P1();
    init();
}

void OrthographicCamera::calculateProjectionMatrix()
{
    Mat4 projectionMatrix;
    projectionMatrix[0] = 2.0f/(m_p1.x-m_p0.x);
    projectionMatrix[1] = 0.0f;
    projectionMatrix[2] = 0.0f;
    projectionMatrix[3] = 0.0f;

    projectionMatrix[4] = 0.0f;
    projectionMatrix[5] = 2.0f/(m_p0.y-m_p1.y);
    projectionMatrix[6] = 0.0f;
    projectionMatrix[7] = 0.0f;

    projectionMatrix[8] = 0.0f;
    projectionMatrix[9] = 0.0f;
    projectionMatrix[10] = -2.0f/(m_farPlane-m_nearPlane);
    projectionMatrix[11] = 0;

    projectionMatrix[12] = -(m_p1.x+m_p0.x)/(m_p1.x-m_p0.x);
    projectionMatrix[13] = -(m_p0.y+m_p1.y)/(m_p0.y-m_p1.y);
    projectionMatrix[14] = -(m_farPlane+m_nearPlane)/(m_farPlane-m_nearPlane);
    projectionMatrix[15] = 1.0f;

    m_projectionMatrix = projectionMatrix;
}

void OrthographicCamera::init()
{
    calculateProjectionMatrix();
}

float OrthographicCamera::width()
{
    return m_width;
}

void OrthographicCamera::setWidth(float width)
{
    m_width = width;
    calculateP0P1();
}

float OrthographicCamera::aspectRatio()
{
    return m_aspectRatio;
}

void OrthographicCamera::setRatio(float ratio)
{
    m_aspectRatio = ratio;
    calculateP0P1();
}

void OrthographicCamera::calculateP0P1()
{
    float height = m_width / m_aspectRatio;
    m_p0.x = -m_width / 2.0;
    m_p0.y = height / 2.0;

    m_p1.x = m_width / 2.0;
    m_p1.y = -height / 2.0;
}
