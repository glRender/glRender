#ifndef POSITIONABLE_HPP
#define POSITIONABLE_HPP

#include "base.h"

#include "mat4.hpp"
#include "vec3.hpp"
#include "vec4.hpp"

namespace glRender
{

class Positionable
{
public:
    virtual ~Positionable() {};
    void setOrigin(const float x, const float y, const float z);
    void setOrigin(const Vec3 & pos);

    virtual void translate(const float x, const float y, const float z);
    virtual void translate(const Vec3 & pos);

    virtual void rotate(const float value, const float x, const float y, const float z);
    virtual void rotate(const float value, const Vec3 & v);

    void setTransformationMatrix(const Mat4 & matrix);
    const Mat4& transformationMatrix() const;

    virtual const Vec3 origin() const;

    const Vec3 up() const;
    const Vec3 front() const;
    const Vec3 right() const;

    const Vec3 upOrig() const;
    const Vec3 frontOrig() const;
    const Vec3 rightOrig() const;

protected:
    Mat4 m_transformationMatrix;
    Mat4 m_modelRotationMatrix;

    Vec4 m_up    = {0.0, 1.0, 0.0, 1.0};
    Vec4 m_front = {0.0, 0.0, -1.0, 1.0};
    Vec4 m_right = {1.0, 0.0, 0.0, 1.0};
};

}

#endif // POSITIONABLE_HPP
