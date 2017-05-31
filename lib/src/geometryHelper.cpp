#include "geometryHelper.hpp"

namespace glRender
{
      Geometry * GeometryHelper::Box(float halfSideSize)
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

            std::vector<uint32_t> indices;
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

            Geometry * geometry = new Geometry(indices);
            geometry->set( "vertex", new Buffer<Vec3>( vertices, BufferType::ArrayBuffer) );
            geometry->set( "uv", new Buffer<Vec2>( uvs, BufferType::ArrayBuffer) );

            return geometry;
      }

      Geometry * GeometryHelper::Plane(const Vec3 & leftUpPoint, const Vec3 & rightUpPoint, const Vec3 & leftBottomPoint, const Vec3 & rightBottomPoint)
      {
            std::vector<Vec3> vertices;
            vertices.push_back( leftUpPoint );
            vertices.push_back( rightUpPoint );
            vertices.push_back( leftBottomPoint );
            vertices.push_back( rightBottomPoint );

            std::vector<Vec2> uvs;
            uvs.push_back( Vec2(0.0, 1.0) );
            uvs.push_back( Vec2(1.0, 1.0) );
            uvs.push_back( Vec2(0.0, 0.0) );
            uvs.push_back( Vec2(1.0, 0.0) );

            std::vector<uint32_t> indices;
            indices.push_back( 0 );
            indices.push_back( 1 );
            indices.push_back( 2 );

            indices.push_back( 2 );
            indices.push_back( 1 );
            indices.push_back( 3 );

            Geometry* geometry = new Geometry(indices);
            geometry->set( "vertex", new Buffer<Vec3>( vertices, BufferType::ArrayBuffer) );
            geometry->set( "uv", new Buffer<Vec2>( uvs, BufferType::ArrayBuffer) );

            return geometry;
      }

      Geometry *GeometryHelper::Line(const Vec3 &p0, const Vec3 &p1, uint32_t segmentsNumber)
      {
          std::vector<Vec3> vertices;

          float step = 1.0 / segmentsNumber;
          Vec3 pn = p1 - p0;
          for (float t=0.0; t<=1.0; t+=step)
          {
              Vec3 p = p0 + pn * t;
              vertices.push_back(p);
          }

          Geometry* geometry = new Geometry();
          geometry->set( "vertex", new Buffer<Vec3>( vertices, BufferType::ArrayBuffer) );

          return geometry;

      }

      Geometry *GeometryHelper::QuadraticBezierCurve(const Vec3 &p0, const Vec3 &p1, const Vec3 &p2, uint32_t segmentsNumber)
      {
          std::vector<Vec3> vertices;

          float step = 1.0 / segmentsNumber;
          for (float t=0.0; t<=1.0; t+=step)
          {
              Vec3 p = pow((1 - t), 2) * p0 + 2 * t * (1 - t) * p1 + pow(t, 2) * p2;
              vertices.push_back(p);
          }

          Geometry* geometry = new Geometry();
          geometry->set( "vertex", new Buffer<Vec3>( vertices, BufferType::ArrayBuffer) );

          return geometry;

      }

}
