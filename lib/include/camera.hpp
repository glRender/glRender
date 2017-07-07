#ifndef __CAMERA_HPP__		
#define __CAMERA_HPP__

#include "base.h"
#include "mat4.hpp"
#include "vec3.hpp"

namespace glRender
{

class Camera
{

public:
    Camera(float nearPlane, float farPlane);

    virtual void calculateProjectionMatrix() = 0;

    void lookAt(const Vec3 & position, const Vec3 & target, const Vec3 & up);

    const Mat4 & projectionMatrix() const;
//    const Mat4 & transformationMatrix() const;

    const Vec3 & position() const;
    const Vec3 & target() const;

    const Vec3 & front() const;
    const Vec3 & right() const;
    const Vec3 & up() const;

    float nearPlane() const;
    void setNearPlane(float nearPlane);

    float farPlane() const;
    void setFarPlane(float farPlane);

    float pitch() const;
    float yaw() const;
    float roll() const;

    void shift(const Vec3 v);

    void setPosition(const Vec3 & pos);
    void setTarget(const Vec3 & target);
    void setDirection(const Vec3 & direction);
    void setEulerAngles(float pitch, float yaw, float roll);

    void setLocalMatrix(const Mat4 & m);
    void setParentsMatrix(const Mat4 & m);
    void setGlobalMatrix(const Mat4 & m);

    const Mat4 & localMatrix() const;
    const Mat4 & parentsMatrix() const;
    const Mat4 & globalMatrix() const;

protected:
    Mat4 m_projectionMatrix;
//    Mat4 m_transformationMatrix;

    Mat4 m_localMatrix;
    Mat4 m_parentsMatrix;
    Mat4 m_globalMatrix;

    Vec3 m_position = {0.0f, 0.0f, 0.0f};
    Vec3 m_target = -Vec3::AXE_Z();
    Vec3 m_direction;

    float m_nearPlane;
    float m_farPlane;

    Vec3 m_front;
    Vec3 m_right;
    Vec3 m_up = Vec3::AXE_Y();

    float m_yaw = 0.0f;
    float m_pitch = 0.0f;
    float m_roll = 0.0f;

};

using CameraPtr = std::shared_ptr<Camera>;

}

#endif /* __CAMERA_HPP__ */
