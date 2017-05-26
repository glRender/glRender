#ifndef BOUNDINGBOX_H
#define BOUNDINGBOX_H

#include "base.h"
#include "vec3.hpp"
#include "ray.hpp"

namespace glRender {

class IBoundingBox
{
public:
    virtual ~IBoundingBox() {};
    virtual bool intersects(const RayPtr ray) const = 0;
    virtual void setOrigin(const Vec3 & origin) = 0;
    void setOrigin(float x, float y, float z);
    virtual const Vec3 & origin() const = 0;
};

}

#endif // BOUNDINGBOX_H
