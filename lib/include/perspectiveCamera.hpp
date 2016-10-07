#ifndef PERSPECTIVECAMERA_H
#define PERSPECTIVECAMERA_H

#include "base.h"
#include "camera.hpp"

namespace glRender
{

class PerspectiveCamera : public Camera
{
private:
    float m_farPlane;
    float m_nearPlane;
    float m_aspectRatio;
    float m_fieldOfView;

public:
    PerspectiveCamera(float fieldOfView, float aspectRatio, float nearPlane, float farPlane);
    void calculateProjectionMatrix();

    float fieldOfView() const;
    void setFieldOfView(float angle);

    float aspectRatio() const;
    void setAspectRatio(float aspectRatio);

    float nearPlane() const;
    void setNearPlane(float nearPlane);

    float farPlane() const;
    void setFarPlane(float farPlane);


};

}

#endif // PERSPECTIVECAMERA_H
