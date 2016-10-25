#include "catch.hpp"
#include "glRender.h"

using namespace glRender;

TEST_CASE("From center along X and Y", "")
{
    AxisalignedBoundingBox bb(Vec3(0,0,0), 0.5f);
    Ray * ray = new Ray(Vec3(0,0,0), Vec3(2,2,0));

    CHECK( bb.intersects(ray) );
}

TEST_CASE("From center against X and Y", "")
{
    AxisalignedBoundingBox bb(Vec3(0,0,0), 0.5f);
    Ray * ray = new Ray(Vec3(0,0,0), Vec3(-2,-2,0));

    CHECK( bb.intersects(ray) );
}

TEST_CASE("Across bb along X", "")
{
    AxisalignedBoundingBox bb(Vec3(0,0,0), 0.5f);
    Ray * ray = new Ray(Vec3(-2,0,0), Vec3(2,0,0));

    CHECK( bb.intersects(ray) );
}

TEST_CASE("Across bb along Y", "")
{
    AxisalignedBoundingBox bb(Vec3(0,0,0), 0.5f);
    Ray * ray = new Ray(Vec3(0,-2,0), Vec3(0,2,0));

    CHECK( bb.intersects(ray) );
}

TEST_CASE("Above bb", "")
{
    AxisalignedBoundingBox bb(Vec3(0,0,0), 0.5f);
    Ray * ray = new Ray(Vec3(-2,2,0), Vec3(2,2,0));

    CHECK( !bb.intersects(ray) );
}

TEST_CASE("Under bb", "")
{
    AxisalignedBoundingBox bb(Vec3(0,0,0), 0.5f);
    Ray * ray = new Ray(Vec3(-2,-2,0), Vec3(2,-2,0));

    CHECK( !bb.intersects(ray) );
}

TEST_CASE("Near left side of bb", "")
{
    AxisalignedBoundingBox bb(Vec3(0,0,0), 0.5f);
    Ray * ray = new Ray(Vec3(-2,-2,0), Vec3(-2,2,0));

    CHECK( !bb.intersects(ray) );
}

TEST_CASE("Near right side of bb", "")
{
    AxisalignedBoundingBox bb(Vec3(0,0,0), 0.5f);
    Ray * ray = new Ray(Vec3(2,-2,0), Vec3(2,2,0));

    CHECK( !bb.intersects(ray) );
}

TEST_CASE("Into bb along X", "")
{
    AxisalignedBoundingBox bb(Vec3(0,0,0), 0.5f);
    Ray * ray = new Ray(Vec3(-0.3,0,0), Vec3(0.3,0,0));

    CHECK( bb.intersects(ray) );
}

TEST_CASE("Into bb along Y", "")
{
    AxisalignedBoundingBox bb(Vec3(0,0,0), 0.5f);
    Ray * ray = new Ray(Vec3(0,-0.3,0), Vec3(0,0.3,0));

    CHECK( bb.intersects(ray) );
}
