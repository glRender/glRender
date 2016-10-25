#ifndef BOUNDINGBOX_H
#define BOUNDINGBOX_H

#include "base.h"
#include "vec3.hpp"

namespace glRender {

class Ray;

class BoundingBox
{
public:
    virtual bool intersects(Ray * ray) const = 0;

};

}

#endif // BOUNDINGBOX_H
