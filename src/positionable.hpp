#ifndef POSITIONABLE_HPP
#define POSITIONABLE_HPP

#include "base.h"

namespace glRender
{

class Positionable
{
protected:
    Mat4 m_transformationMatrix;
    Mat4 m_modelRotationMatrix;
    
    Vec4 m_up    = {0.0, 1.0, 0.0, 1.0};
    Vec4 m_front = {0.0, 0.0, -1.0, 1.0};
    Vec4 m_right = {1.0, 0.0, 0.0, 1.0};

public:
    void setPosition(const float x, const float y, const float z);
    void setPosition(const Vec3 & pos);

    virtual void translate(const float x, const float y, const float z);
    virtual void translate(const Vec3 & pos);

    virtual void rotate(const float value, const float x, const float y, const float z);
    virtual void rotate(const float value, const Vec3 & v);

    void setTransformationMatrix(const Mat4 & matrix);
    const Mat4& transformationMatrix() const;

    virtual const Vec3 position() const;

    const Vec3 up() const;
    const Vec3 front() const;
    const Vec3 right() const;

    const Vec3 upOrig() const;
    const Vec3 frontOrig() const;
    const Vec3 rightOrig() const;


};

}

#endif // POSITIONABLE_HPP
