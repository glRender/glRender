#pragma once

#include "base.h"

namespace glRender
{
    class Geometry;
    class Vec3;

    class GeometryHelper
    {
    public:
        static std::shared_ptr<Geometry> Box(float halfSideSize=1.0f);
        static std::shared_ptr<Geometry> Plane(const Vec3 & leftUpPoint, const Vec3 & rightUpPoint, const Vec3 & leftBottomPoint, const Vec3 & rightBottomPoint);
        static std::shared_ptr<Geometry> Line(const Vec3 &p0, const Vec3 &p1, uint32_t segmentsNumber = 2);
        static std::shared_ptr<Geometry> QuadraticBezierCurve(const Vec3 & p0, const Vec3 & p1, const Vec3 & p2, uint32_t segmentsNumber);
        static std::shared_ptr<Geometry> Arrows();

    };

}
