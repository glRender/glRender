#ifndef RAY_H
#define RAY_H

#include "base.h"
#include "vec3.hpp"

namespace glRender {

class Ray
{
public:
    Ray(const Vec3 & origin, const Vec3 & target);
    const Vec3 origin() const;
    const Vec3 target() const;
    const Vec3 dir() const;

    void setOrigin(const Vec3 & origin);
    void setTarget(const Vec3 & target);

private:
    Vec3 m_origin;
    Vec3 m_target;
};

}

#endif // RAY_H
