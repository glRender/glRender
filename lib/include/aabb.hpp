#ifndef AXISALIGNEDBOUNDINGBOX_H
#define AXISALIGNEDBOUNDINGBOX_H

#include "boundingBox.hpp"
#include "vec3.hpp"

namespace glRender {

class AABB : public IBoundingBox
{
public:
    AABB(const Vec3 & origin, float halfSide);
    const Vec3 & origin() const override;
    float halfSide() const;
    const Vec3 & min();
    const Vec3 & max();

    void setOrigin(const Vec3 & origin) override;
    void setHalfSide(float halfSide);

    bool intersects(const RayPtr ray) const override;

private:
    void _updateMinMax();

private:
    Vec3 m_center;
    float m_halfSide;
    Vec3 m_min;
    Vec3 m_max;
};

}

#endif // AXISALIGNEDBOUNDINGBOX_H
