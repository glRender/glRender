#ifndef __CAMERA_HPP__		
#define __CAMERA_HPP__

#include "base.h"

namespace glRender
{

class Camera
{

public:
    Camera();

    virtual void calculateProjectionMatrix() = 0;

    void lookAt(const Vec3 & position, const Vec3 & target, const Vec3 & up);

    const Mat4 & projectionMatrix() const;
    const Mat4 & transformationMatrix() const;

    const Vec3 & position() const;
    const Vec3 & target() const;
    const Vec3 & up() const;

protected:
    Mat4 m_projectionMatrix;
    Mat4 m_transformationMatrix;
    Vec3 m_position = {0.0f, 0.0f, 0.0f};
    Vec3 m_target = -Vec3::AXE_Z();
    Vec3 m_up = Vec3::AXE_Y();

};

}

#endif /* __CAMERA_HPP__ */
