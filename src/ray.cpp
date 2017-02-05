#include "ray.hpp"

using namespace glRender;

Ray::Ray(const Vec3 &origin, const Vec3 &target)
    : m_origin(origin)
    , m_target(target)
{

}

const Vec3 Ray::origin() const
{
    return m_origin;
}

const Vec3 Ray::target() const
{
    return m_target;
}

const Vec3 Ray::dir() const
{
    Vec3 d = m_target - m_origin;
    d.normalize();
    return d;
}

void Ray::setOrigin(const Vec3 &origin)
{
    m_origin = origin;
}

void Ray::setTarget(const Vec3 &target)
{
    m_target = target;
}
