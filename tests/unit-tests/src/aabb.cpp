#include "catch.hpp"
#include "glRender.h"

using namespace glRender;

TEST_CASE("From center along X and Y", "")
{
    AABB bb(Vec3(0,0,0), 0.5f);
    RayPtr ray = std::make_shared<Ray>(Vec3(0,0,0), Vec3(2,2,0));

    CHECK( bb.intersects(ray) );
}

TEST_CASE("From center against X and Y", "")
{
    AABB bb(Vec3(0,0,0), 0.5f);
    RayPtr ray = RayPtr(new Ray(Vec3(0,0,0), Vec3(-2,-2,0)));

    CHECK( bb.intersects(ray) );
}

TEST_CASE("Across bb along X", "")
{
    AABB bb(Vec3(0,0,0), 0.5f);
    RayPtr ray = RayPtr(new Ray(Vec3(-2,0,0), Vec3(2,0,0)));

    CHECK( bb.intersects(ray) );
}

TEST_CASE("Across bb along Y", "")
{
    AABB bb(Vec3(0,0,0), 0.5f);
    RayPtr ray = RayPtr(new Ray(Vec3(0,-2,0), Vec3(0,2,0)));

    CHECK( bb.intersects(ray) );
}

TEST_CASE("Above bb", "")
{
    AABB bb(Vec3(0,0,0), 0.5f);
    RayPtr ray = RayPtr(new Ray(Vec3(-2,2,0), Vec3(2,2,0)));

    CHECK( !bb.intersects(ray) );
}

TEST_CASE("Under bb", "")
{
    AABB bb(Vec3(0,0,0), 0.5f);
    RayPtr ray = RayPtr(new Ray(Vec3(-2,-2,0), Vec3(2,-2,0)));

    CHECK( !bb.intersects(ray) );
}

TEST_CASE("Near left side of bb", "")
{
    AABB bb(Vec3(0,0,0), 0.5f);
    RayPtr ray = RayPtr(new Ray(Vec3(-2,-2,0), Vec3(-2,2,0)));

    CHECK( !bb.intersects(ray) );
}

TEST_CASE("Near right side of bb", "")
{
    AABB bb(Vec3(0,0,0), 0.5f);
    RayPtr ray = RayPtr(new Ray(Vec3(2,-2,0), Vec3(2,2,0)));

    CHECK( !bb.intersects(ray) );
}

TEST_CASE("Into bb along X", "")
{
    AABB bb(Vec3(0,0,0), 0.5f);
    RayPtr ray = RayPtr(new Ray(Vec3(-0.3,0,0), Vec3(0.3,0,0)));

    CHECK( bb.intersects(ray) );
}

TEST_CASE("Into bb along Y", "")
{
    AABB bb(Vec3(0,0,0), 0.5f);
    RayPtr ray = RayPtr(new Ray(Vec3(0,-0.3,0), Vec3(0,0.3,0)));

    CHECK( bb.intersects(ray) );
}

TEST_CASE("Into bb along Z", "")
{
    AABB bb(Vec3(0,0,0), 0.5f);
    RayPtr ray = RayPtr(new Ray(Vec3(0,5,0), Vec3(-5,-5,0)));

    CHECK( !bb.intersects(ray) );
}

TEST_CASE("Fuzze test", "")
{
    Vec3 vertices[] = {
        Vec3(-1.0, 1.0, -1.0),
        Vec3( 1.0, 1.0, -1.0),
        Vec3(-1.0,-1.0, -1.0),
        Vec3( 1.0,-1.0, -1.0),

        Vec3(-1.0, 1.0, 1.0),
        Vec3( 1.0, 1.0, 1.0),
        Vec3(-1.0,-1.0, 1.0),
        Vec3( 1.0,-1.0, 1.0),
    };

    AABB bb(Vec3(0,0,0), 1.01f);

    for (auto & p : vertices)
    {
        for (uint i=0; i<=10; i++)
        {
            for (uint j=0; j<=10; j++)
            {
                for (uint k=0; k<=10; k++)
                {
                    RayPtr ray = std::make_shared<Ray>(p, Vec3(i/10.0, j/10.0, k/10.0));
                    CHECK( bb.intersects(ray) );
                    ray = std::make_shared<Ray>(Vec3(i/10.0, j/10.0, k/10.0), p);
                    CHECK( bb.intersects(ray) );

                }
            }
        }
    }
}
