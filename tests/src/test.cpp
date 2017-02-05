#include "catch.hpp"
#include "glRender.h"

using namespace glRender;

TEST_CASE("Description", "[test]")
{
    Vec3 d;
    d.x = 3;

    CHECK( d.x == 3 );
}
