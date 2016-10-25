#ifndef AXISALIGNEDBOUNDINGBOX_H
#define AXISALIGNEDBOUNDINGBOX_H

#include "base.h"
#include "boundingBox.hpp"
#include "vec3.hpp"

namespace glRender {

class AxisalignedBoundingBox : public BoundingBox
{
public:
    AxisalignedBoundingBox(const Vec3 & center, float halfSide);
    const Vec3 & center() const;
    float halfSide() const;

    void setCenter(const Vec3 & center);
    void setHalfSide(float halfSide);

    virtual bool intersects(Ray * ray) const;

private:
    Vec3 m_center;
    float m_halfSide;
};

}

#endif // AXISALIGNEDBOUNDINGBOX_H
