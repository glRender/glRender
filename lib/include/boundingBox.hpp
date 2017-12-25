#ifndef BOUNDINGBOX_H
#define BOUNDINGBOX_H

#include "base.h"

namespace glRender {

class Ray;
class Vec3;

class IBoundingBox
{
public:
    virtual ~IBoundingBox() {};
    virtual bool intersects(const std::shared_ptr<Ray> ray) const = 0;
    virtual void setOrigin(const Vec3 & origin) = 0;
    void setOrigin(float x, float y, float z);
    virtual const Vec3 & origin() const = 0;
};

}

#endif // BOUNDINGBOX_H
