#pragma once

#include "base.h"

#include "camera.hpp"

namespace glRender
{

class OrthographicCamera : public Camera
{
public:
    /**
     * @param width The width of viewport in normalized units
     * @param aspectRatio The ratio of width and height of viewport
     * @param nearPlane The distance to near plane in normalized units
     * @param farPlane The distance to far plane in normalized units
     */
    OrthographicCamera(float width, float aspectRatio, float nearPlane, float farPlane);
    void calculateProjectionMatrix() override;
    void init();  /**< Method for avoid call calculateProjectionMatrix in constructor (virtual method)*/

    float width();
    void setWidth(float width);

    float aspectRatio();
    void setRatio(float aspectRatio);

private:
    void calculateP0P1();
private:
    float m_width;
    float m_aspectRatio;
    Vec2 m_p0;
    Vec2 m_p1;
};

}
