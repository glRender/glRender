#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file

#include "catch.hpp"
#include "glRender.h"

using namespace glRender;

SCENARIO( "Class Vec3 filling", "[Vec3]" ){
    GIVEN( "Empty Vec3" ) {
        Vec3 v;

        REQUIRE( v[0] == 0.0 );
        REQUIRE( v[1] == 0.0 );
        REQUIRE( v[2] == 0.0 );

        REQUIRE( v.x == 0.0 );
        REQUIRE( v.y == 0.0 );
        REQUIRE( v.z == 0.0 );

        WHEN( "method Vec3::set invoked" ) {
            v.set(1.0, 2.0, 3.0);

            THEN( "data appears into" ) {
                REQUIRE( v.x == 1.0 );
                REQUIRE( v.y == 2.0 );
                REQUIRE( v.z == 3.0 );
            }
        }

        WHEN( "operator [] invoked" ) {
            v[0] = 333.0f;
            v[1] = 444.0f;
            v[2] = 555.0f;

            THEN( "data appears into" ) {
                REQUIRE( v[0] == 333.0f );
                REQUIRE( v[1] == 444.0f );
                REQUIRE( v[2] == 555.0f );

                REQUIRE( v.x == 333.0f );
                REQUIRE( v.y == 444.0f );
                REQUIRE( v.z == 555.0f );

            }
        }

    }
}
