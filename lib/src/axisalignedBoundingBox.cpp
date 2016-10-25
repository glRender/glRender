#include "axisalignedBoundingBox.hpp"
#include "ray.hpp"

using namespace glRender;

bool isBetween(float a, float b, float c)
{
    return (c > a) and (c < b);
}

AxisalignedBoundingBox::AxisalignedBoundingBox(const Vec3 & center, float halfSide)
    : m_center(center)
    , m_halfSide(halfSide)
{

}

const Vec3 &AxisalignedBoundingBox::center() const
{
    return m_center;
}

float AxisalignedBoundingBox::halfSide() const
{
    return m_halfSide;
}

void AxisalignedBoundingBox::setCenter(const Vec3 &center)
{
    m_center = center;
}

void AxisalignedBoundingBox::setHalfSide(float halfSide)
{
    m_halfSide = halfSide;
}

bool AxisalignedBoundingBox::intersects(Ray *ray) const
{
    Vec3 bottomLeft(m_center - Vec3(m_halfSide, m_halfSide, m_halfSide));
    Vec3 upRight(m_center + Vec3(m_halfSide, m_halfSide, m_halfSide));

    bool isIntersects = true;



    if (isBetween(ray->origin().x, ray->target().x, bottomLeft.x) ||
        isBetween(ray->origin().x, ray->target().x, upRight.x) ||
        isBetween(bottomLeft.x, upRight.x, ray->origin().x) ||
        isBetween(bottomLeft.x, upRight.x, ray->target().x))
    {
//        std::cout << "Intersects with ray in X" << std::endl;
    }
    else
    {
        isIntersects = false;
    }

    if (isBetween(ray->origin().y, ray->target().y, bottomLeft.y) ||
        isBetween(ray->origin().y, ray->target().y, upRight.y) ||
        isBetween(bottomLeft.y, upRight.y, ray->origin().y) ||
        isBetween(bottomLeft.y, upRight.y, ray->target().y))
    {
//        std::cout << "Intersects with ray in Y" << std::endl;
    }
    else
    {
        isIntersects = false;
    }

    if (isBetween(ray->origin().z, ray->target().z, bottomLeft.z) ||
        isBetween(ray->origin().z, ray->target().z, upRight.z) ||
        isBetween(bottomLeft.z, upRight.z, ray->origin().z) ||
        isBetween(bottomLeft.z, upRight.z, ray->target().z))
    {
//        std::cout << "Intersects with ray in Z" << std::endl;
    }
    else
    {
        isIntersects = false;
    }

    return isIntersects;
}

