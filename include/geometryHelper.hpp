#ifndef __GEOMETRYHELPER_H__
#define __GEOMETRYHELPER_H__

#include "base.h"

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
	};

}

#endif /* __GEOMETRYHELPER_H__ */
