#ifndef __GEOMETRYHELPER_H__
#define __GEOMETRYHELPER_H__

#include "base.h"

#include "vec3.hpp"
#include "attribute.h"
#include "geometryBuffer.hpp"
#include "geometry.hpp"

namespace glRender
{
    class GeometryHelper
    {
    public:
        static Geometry * Cube(float halfSideSize=1.0f);
        static Geometry * Plane(const Vec3 & leftUpPoint, const Vec3 & rightUpPoint, const Vec3 & leftBottomPoint, const Vec3 & rightBottomPoint);
        static Geometry * Line(const Vec3 &p0, const Vec3 &p1, uint segmentsNumber = 2);
        static Geometry * QuadraticBezierCurve(const Vec3 & p0, const Vec3 & p1, const Vec3 & p2, uint segmentsNumber);
    };

}

#endif /* __GEOMETRYHELPER_H__ */
