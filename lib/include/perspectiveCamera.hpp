#ifndef PERSPECTIVECAMERA_H
#define PERSPECTIVECAMERA_H

#include "base.h"

#include "camera.hpp"

namespace glRender
{

/**
 * @param fieldOfView Field of view in degrees
 * @param aspectRatio The ratio of width and height of viewport
 * @param nearPlane The distance to near plane in normalized units
 * @param farPlane The distance to far plane in normalized units
 */
class PerspectiveCamera : public Camera
{
public:
    PerspectiveCamera(float fieldOfView, float aspectRatio, float nearPlane, float farPlane);
    void calculateProjectionMatrix() override;
    void init();  /**< Method for avoid call calculateProjectionMatrix in constructor (virtual method)*/

    float fieldOfView() const;
    void setFieldOfView(float angle);

    float aspectRatio() const;
    void setAspectRatio(float aspectRatio);
private:
    float m_fieldOfView;
    float m_aspectRatio;
};

using PerspectiveCameraPtr = std::shared_ptr<PerspectiveCamera>;

}
#endif // PERSPECTIVECAMERA_H
