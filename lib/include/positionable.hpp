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

    Mat4 & transforms();

    virtual void translate(const float x, const float y, const float z);
    virtual void translate(const Vec3 & pos);

    virtual void rotate(const float value, const float x, const float y, const float z);
    virtual void rotate(const float value, const Vec3 & v);

//    void setTransformationMatrix(const Mat4 & matrix);
//    const Mat4& transformationMatrix() const;

    virtual const Vec3 origin() const;

    const Vec3 up() const;
    const Vec3 front() const;
    const Vec3 right() const;

    const Vec3 upOrig() const;
    const Vec3 frontOrig() const;
    const Vec3 rightOrig() const;

    void setLocalMatrix(const Mat4 & m);
    void setParentsMatrix(const Mat4 & m);
    void setGlobalMatrix(const Mat4 & m);

    const Mat4 & localMatrix() const;
    const Mat4 & parentsMatrix() const;
    inline const Mat4 & globalMatrix() const
    {
        return m_globalMatrix;
    }

protected:
//    Mat4 m_transformationMatrix;
    Mat4 m_modelRotationMatrix;

    Vec4 m_up    = {0.0, 1.0, 0.0, 1.0};
    Vec4 m_front = {0.0, 0.0, -1.0, 1.0};
    Vec4 m_right = {1.0, 0.0, 0.0, 1.0};

    Mat4 m_localMatrix;
    Mat4 m_parentsMatrix;
    Mat4 m_globalMatrix;

};

}

#endif // POSITIONABLE_HPP
