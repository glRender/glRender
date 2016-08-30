#ifndef __CAMERA_HPP__		
#define __CAMERA_HPP__

#include "base.h"
#include "positionable.hpp"

namespace glRender
{

class Camera : public Positionable
{
protected:
    Mat4 m_projectionMatrix;
    Mat4 m_transformationMatrix;

public:
    Camera();

	void lookAt(const Vec3 & position, const Vec3 & target, const Vec3 & up);

    const Mat4 & projectionMatrix() const;
	void setProjectionMatrix(const Mat4 & matrix);

    const Mat4 & transformationMatrix() const;

    virtual void calculateProjectionMatrix() = 0;

    void translate(const float x, const float y, const float z) override;
    void translate(const Vec3 & pos) override;

    void rotate(const float value, const float x, const float y, const float z);
    void rotate(const float value, const Vec3 & v);
};

}

#endif /* __CAMERA_HPP__ */
