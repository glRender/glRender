#ifndef PERSPECTIVECAMERA_H
#define PERSPECTIVECAMERA_H

#include "base.h"

#include "camera.hpp"

namespace glRender
{

class PerspectiveCamera : public Camera
{
public:
    PerspectiveCamera(float fieldOfView, float aspectRatio, float nearPlane, float farPlane);
    void calculateProjectionMatrix() override;
    void init();

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
