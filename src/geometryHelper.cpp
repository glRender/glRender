#include "geometryHelper.hpp"

namespace glRender
{
      Geometry * GeometryHelper::Cube(float halfSideSize)
      {
            std::vector<Vec3> vertices;
            /////////////
            vertices.push_back( Vec3(-halfSideSize, halfSideSize, -halfSideSize) );
            vertices.push_back( Vec3(halfSideSize, halfSideSize, -halfSideSize) );
            vertices.push_back( Vec3(-halfSideSize, -halfSideSize, -halfSideSize) );
            vertices.push_back( Vec3(halfSideSize, -halfSideSize, -halfSideSize) );
            /////////////
            vertices.push_back( Vec3(-halfSideSize, halfSideSize, halfSideSize) );
            vertices.push_back( Vec3(halfSideSize, halfSideSize, halfSideSize) );
            vertices.push_back( Vec3(-halfSideSize, -halfSideSize, halfSideSize) );
            vertices.push_back( Vec3(halfSideSize, -halfSideSize, halfSideSize) );

            std::vector<Vec2> uvs;
            uvs.push_back( Vec2(0.0f, 1.0f) );
            uvs.push_back( Vec2(1.0f, 1.0f) );
            uvs.push_back( Vec2(0.0f, 0.0f) );
            uvs.push_back( Vec2(1.0f, 0.0f) );
            uvs.push_back( Vec2(0.0f, 1.0f) );
            uvs.push_back( Vec2(1.0f, 1.0f) );
            uvs.push_back( Vec2(0.0f, 0.0f) );
            uvs.push_back( Vec2(1.0f, 0.0f) );

            std::vector<GLuint> indices;
            /////////////////////
            indices.push_back( 0 );
            indices.push_back( 1 );
            indices.push_back( 2 );

            indices.push_back( 2 );
            indices.push_back( 1 );
            indices.push_back( 3 );

            /////////////////////
            indices.push_back( 4 );
            indices.push_back( 5 );
            indices.push_back( 6 );

            indices.push_back( 6 );
            indices.push_back( 5 );
            indices.push_back( 7 );

            /////////////////////
            indices.push_back( 4 );
            indices.push_back( 5 );
            indices.push_back( 0 );

            indices.push_back( 0 );
            indices.push_back( 5 );
            indices.push_back( 1 );

            /////////////////////
            indices.push_back( 6 );
            indices.push_back( 7 );
            indices.push_back( 2 );

            indices.push_back( 2 );
            indices.push_back( 7 );
            indices.push_back( 3 );

            /////////////////////
            indices.push_back( 1 );
            indices.push_back( 5 );
            indices.push_back( 3 );

            indices.push_back( 3 );
            indices.push_back( 5 );
            indices.push_back( 7 );

            /////////////////////
            indices.push_back( 0 );
            indices.push_back( 4 );
            indices.push_back( 2 );

            indices.push_back( 2 );
            indices.push_back( 4 );
            indices.push_back( 6 );

            Geometry * geometry = new Geometry();
            geometry->setGeometryBuffer( "vertex", new GeometryBufferVec3( vertices ) );
            geometry->setGeometryBuffer( "uv", new GeometryBufferVec2( uvs ) );
            geometry->setGeometryBuffer( "index", new GeometryBufferUint( indices ) );

            return geometry;
      }

      Geometry * GeometryHelper::Plane(const Vec3 & leftUpPoint, const Vec3 & rightUpPoint, const Vec3 & leftBottomPoint, const Vec3 & rightBottomPoint)
      {
            std::vector<Vec3> vertices;
            vertices.push_back( leftUpPoint );
            vertices.push_back( rightUpPoint );
            vertices.push_back( leftBottomPoint );
            vertices.push_back( rightBottomPoint );

            std::vector<Vec2> uv;
            uv.push_back( Vec2(0.0, 1.0) );
            uv.push_back( Vec2(1.0, 1.0) );
            uv.push_back( Vec2(0.0, 0.0) );
            uv.push_back( Vec2(1.0, 0.0) );

            std::vector<GLuint> indices;
            indices.push_back( 0 );
            indices.push_back( 1 );
            indices.push_back( 2 );

            indices.push_back( 2 );
            indices.push_back( 1 );
            indices.push_back( 3 );

            Geometry* geometry = new Geometry();
            geometry->setGeometryBuffer( "vertex", new GeometryBufferVec3( vertices ) );
            geometry->setGeometryBuffer( "uv", new GeometryBufferVec2( uv ) );
            geometry->setGeometryBuffer( "index", new GeometryBufferUint( indices ) );

            return geometry;
      }

}
