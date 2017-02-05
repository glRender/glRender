#ifndef BOUNDINGBOX_H
#define BOUNDINGBOX_H

#include "base.h"
#include "vec3.hpp"

namespace glRender {

class Ray;

class IBoundingBox
{
public:
    virtual ~IBoundingBox() {};
    virtual bool intersects(Ray * ray) const = 0;
    virtual void setOrigin(const Vec3 & origin) = 0;
    void setOrigin(float x, float y, float z);
    virtual const Vec3 & origin() const = 0;
};

}

#endif // BOUNDINGBOX_H
