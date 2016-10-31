#include "base.h"
#include "aabb.hpp"
#include "ray.hpp"
#include "mat4.hpp"
#include "vec4.hpp"
#include "vec3.hpp"

using namespace glRender;

AABB::AABB(const Vec3 & center, float halfSide)
    : m_center(center)
    , m_halfSide(halfSide)
{
    _updateMinMax();
}

const Vec3 &AABB::origin() const
{
    return m_center;
}

float AABB::halfSide() const
{
    return m_halfSide;
}

const Vec3 &AABB::min()
{
    return m_min;
}

const Vec3 &AABB::max()
{
    return m_max;
}

void AABB::setOrigin(const Vec3 & center)
{
    m_center = center;
    _updateMinMax();
}

void AABB::setHalfSide(float halfSide)
{
    m_halfSide = halfSide;
    _updateMinMax();
}

bool AABB::intersects(Ray * ray) const
{
    float tmin, tmax, tymin, tymax, tzmin, tzmax;
    if (ray->target().x >= 0)
    {
        tmin = (m_min.x - ray->origin().x) / ray->target().x;
        tmax = (m_max.x - ray->origin().x) / ray->target().x;
    }
    else
    {
        tmin = (m_max.x - ray->origin().x) / ray->target().x;
        tmax = (m_min.x - ray->origin().x) / ray->target().x;
    }

    if (ray->target().y >= 0)
    {
        tymin = (m_min.y - ray->origin().y) / ray->target().y;
        tymax = (m_max.y - ray->origin().y) / ray->target().y;
    }
    else
    {
        tymin = (m_max.y - ray->origin().y) / ray->target().y;
        tymax = (m_min.y - ray->origin().y) / ray->target().y;
    }

    if ( (tmin > tymax) || (tymin > tmax) )
        return false;

    if (tymin > tmin)
        tmin = tymin;
    if (tymax < tmax)
        tmax = tymax;
    if (ray->target().z >= 0)
    {
        tzmin = (m_min.z - ray->origin().z) / ray->target().z;
        tzmax = (m_max.z - ray->origin().z) / ray->target().z;
    }
    else
    {
        tzmin = (m_max.z - ray->origin().z) / ray->target().z;
        tzmax = (m_min.z - ray->origin().z) / ray->target().z;
    }

    if ( (tmin > tzmax) || (tzmin > tmax) )
        return false;
    if (tzmin > tmin)
        tmin = tzmin;
    if (tzmax < tmax)
        tmax = tzmax;
    return tmin < tmax;
}

void AABB::_updateMinMax()
{
    m_min = m_center - Vec3(m_halfSide, m_halfSide, m_halfSide);
    m_max = m_center + Vec3(m_halfSide, m_halfSide, m_halfSide);
}
