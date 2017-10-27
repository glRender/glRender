#include "boundingBox.hpp"

#include "vec3.hpp"
#include "ray.hpp"

using namespace glRender;

void IBoundingBox::setOrigin(float x, float y, float z)
{
    setOrigin(Vec3(x, y, z));
}
