#include "geometryHelper.hpp"

#include "vec2.hpp"
#include "vec3.hpp"
#include "geometry.hpp"

namespace glRender
{
      std::shared_ptr<Geometry> GeometryHelper::Box(float halfSideSize)
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

            std::shared_ptr<Geometry> geometry = std::make_shared<Geometry>(indices);
            geometry->set( "vertex", new Buffer<Vec3>( vertices, BufferType::ArrayBuffer) );
            geometry->set( "uv", new Buffer<Vec2>( uvs, BufferType::ArrayBuffer) );

            return geometry;
      }

      std::shared_ptr<Geometry> GeometryHelper::Plane(const Vec3 & leftUpPoint, const Vec3 & rightUpPoint, const Vec3 & leftBottomPoint, const Vec3 & rightBottomPoint)
      {
            std::vector<Vec3> vertices;
            vertices.push_back( leftUpPoint );
            vertices.push_back( rightUpPoint );
            vertices.push_back( leftBottomPoint );
            vertices.push_back( rightBottomPoint );

            std::vector<Vec2> uvs;
            uvs.push_back( Vec2(0.0, 0.0) );
            uvs.push_back( Vec2(1.0, 0.0) );
            uvs.push_back( Vec2(0.0, 1.0) );
            uvs.push_back( Vec2(1.0, 1.0) );

            std::vector<uint32_t> indices;
            indices.push_back( 0 );
            indices.push_back( 1 );
            indices.push_back( 2 );

            indices.push_back( 2 );
            indices.push_back( 1 );
            indices.push_back( 3 );

            std::shared_ptr<Geometry> geometry = std::make_shared<Geometry>(indices);
            geometry->set( "vertex", new Buffer<Vec3>( vertices, BufferType::ArrayBuffer) );
            geometry->set( "uv", new Buffer<Vec2>( uvs, BufferType::ArrayBuffer) );

            return geometry;
      }

      std::shared_ptr<Geometry> GeometryHelper::Line(const Vec3 &p0, const Vec3 &p1, uint32_t segmentsNumber)
      {
          std::vector<Vec3> vertices;

          float step = 1.0 / segmentsNumber;
          Vec3 pn = p1 - p0;
          for (float t=0.0; t<=1.0; t+=step)
          {
              Vec3 p = p0 + pn * t;
              vertices.push_back(p);
          }

          std::shared_ptr<Geometry> geometry = std::make_shared<Geometry>();
          geometry->set( "vertex", new Buffer<Vec3>( vertices, BufferType::ArrayBuffer) );

          return geometry;

      }

      std::shared_ptr<Geometry> GeometryHelper::QuadraticBezierCurve(const Vec3 &p0, const Vec3 &p1, const Vec3 &p2, uint32_t segmentsNumber)
      {
          std::vector<Vec3> vertices;

          float step = 1.0 / segmentsNumber;
          for (float t=0.0; t<=1.0; t+=step)
          {
              Vec3 p = pow((1 - t), 2) * p0 + 2 * t * (1 - t) * p1 + pow(t, 2) * p2;
              vertices.push_back(p);
          }

          std::shared_ptr<Geometry> geometry = std::make_shared<Geometry>();
          geometry->set( "vertex", new Buffer<Vec3>( vertices, BufferType::ArrayBuffer) );

          return geometry;

      }

      std::shared_ptr<Geometry> GeometryHelper::Arrows()
      {
            std::vector<Vec3> vertices;
            vertices.push_back( Vec3( 0.000000f, -2.000000f, -6.123888f));
            vertices.push_back( Vec3( 0.000000f, -0.000000f, -11.123888f));
            vertices.push_back( Vec3( 1.732051f, 1.000000f, -6.123888f));
            vertices.push_back( Vec3( -1.732051f, 1.000000f, -6.123888f));
            vertices.push_back( Vec3( 0.037558f, -0.929151f, 0.511201f));
            vertices.push_back( Vec3( 0.869328f, 1.005464f, -0.975603f));
            vertices.push_back( Vec3( -0.833239f, 0.549071f, 0.574224f));
            vertices.push_back( Vec3( 0.898812f, 0.540510f, -6.007830f));
            vertices.push_back( Vec3( 0.032787f, -0.959490f, -6.007830f));
            vertices.push_back( Vec3( -0.833239f, 0.540510f, -6.007830f));
            vertices.push_back( Vec3( 6.123888f, -0.000000f, -2.000000f));
            vertices.push_back( Vec3( 11.123888f, -0.000000f, 0.000000f));
            vertices.push_back( Vec3( 6.123888f, -1.732051f, 1.000000f));
            vertices.push_back( Vec3( 6.123888f, 1.732051f, 1.000000f));
            vertices.push_back( Vec3( 0.899195f, 0.811052f, 0.540511f));
            vertices.push_back( Vec3( 6.007830f, -0.898812f, 0.540511f));
            vertices.push_back( Vec3( 6.007830f, -0.032787f, -0.959489f));
            vertices.push_back( Vec3( 6.007830f, 0.833238f, 0.540511f));
            vertices.push_back( Vec3( 0.000000f, 6.123888f, -2.000000f));
            vertices.push_back( Vec3( 0.000000f, 11.123888f, 0.000000f));
            vertices.push_back( Vec3( 1.732051f, 6.123888f, 1.000000f));
            vertices.push_back( Vec3( -1.732051f, 6.123888f, 1.000000f));
            vertices.push_back( Vec3( 0.898812f, 6.007830f, 0.540511f ));
            vertices.push_back( Vec3( 0.032787f, 6.007830f, -0.959489f ));
            vertices.push_back( Vec3( -0.833239f, 6.007830f, 0.540511f ));

            std::vector<uint32_t> indices;
            indices.push_back( 2);
            indices.push_back(1);
            indices.push_back( 3);

            indices.push_back( 0);
            indices.push_back( 1);
            indices.push_back( 2);

            indices.push_back( 3);
            indices.push_back( 1);
            indices.push_back( 0);

            indices.push_back( 0);
            indices.push_back( 2);
            indices.push_back( 3);

            indices.push_back( 4);
            indices.push_back( 6);
            indices.push_back( 9);

            indices.push_back( 7);
            indices.push_back( 8);
            indices.push_back( 9);

            indices.push_back( 5);
            indices.push_back( 7);
            indices.push_back( 9);

            indices.push_back( 5);
            indices.push_back( 4);
            indices.push_back( 8);

            indices.push_back( 2);
            indices.push_back( 7);
            indices.push_back( 8);

            indices.push_back( 2);
            indices.push_back( 3);
            indices.push_back( 9);

            indices.push_back( 3);
            indices.push_back( 9);
            indices.push_back( 8);

            indices.push_back( 12);
            indices.push_back( 11);
            indices.push_back( 13);

            indices.push_back( 10);
            indices.push_back( 11);
            indices.push_back( 12);

            indices.push_back( 13);
            indices.push_back( 11);
            indices.push_back( 10);

            indices.push_back( 10);
            indices.push_back( 12);
            indices.push_back( 13);

            indices.push_back( 15);
            indices.push_back( 16);
            indices.push_back( 17);

            indices.push_back( 5);
            indices.push_back( 23);
            indices.push_back( 22);

            indices.push_back( 5);
            indices.push_back( 14);
            indices.push_back( 17);

            indices.push_back( 12);
            indices.push_back( 15);
            indices.push_back( 16);

            indices.push_back( 12);
            indices.push_back( 13);
            indices.push_back( 17);

            indices.push_back( 13);
            indices.push_back( 17);
            indices.push_back( 16);

            indices.push_back( 20);
            indices.push_back( 19);
            indices.push_back( 21);

            indices.push_back( 18);
            indices.push_back( 19);
            indices.push_back( 20);

            indices.push_back( 21);
            indices.push_back( 19);
            indices.push_back( 18);

            indices.push_back( 18);
            indices.push_back( 20);
            indices.push_back( 21);

            indices.push_back( 22);
            indices.push_back( 23);
            indices.push_back( 24);

            indices.push_back( 14);
            indices.push_back( 22);
            indices.push_back( 24);

            indices.push_back( 20);
            indices.push_back( 22);
            indices.push_back( 23);

            indices.push_back( 20);
            indices.push_back( 21);
            indices.push_back( 24);

            indices.push_back( 21);
            indices.push_back( 24);
            indices.push_back( 23);

            indices.push_back( 14);
            indices.push_back( 4);
            indices.push_back( 15);

            indices.push_back( 5);
            indices.push_back( 6);
            indices.push_back( 24);

            indices.push_back( 4);
            indices.push_back( 14);
            indices.push_back( 6);

            indices.push_back( 5);
            indices.push_back( 16);
            indices.push_back( 15);

            indices.push_back( 8);
            indices.push_back( 4);
            indices.push_back( 9);

            indices.push_back( 6);
            indices.push_back( 5);
            indices.push_back( 9);

            indices.push_back( 7);
            indices.push_back( 5);
            indices.push_back( 8);

            indices.push_back( 0);
            indices.push_back( 2);
            indices.push_back( 8);

            indices.push_back( 7);
            indices.push_back( 2);
            indices.push_back( 9);

            indices.push_back( 0);
            indices.push_back( 3);
            indices.push_back( 8);

            indices.push_back( 14);
            indices.push_back( 5);
            indices.push_back( 22);

            indices.push_back( 16);
            indices.push_back( 5);
            indices.push_back( 17);

            indices.push_back( 10);
            indices.push_back( 12);
            indices.push_back( 16);

            indices.push_back( 15);
            indices.push_back( 12);
            indices.push_back( 17);

            indices.push_back( 10);
            indices.push_back( 13);
            indices.push_back( 16);

            indices.push_back( 8);
            indices.push_back( 14);
            indices.push_back( 24);

            indices.push_back( 18);
            indices.push_back( 20);
            indices.push_back( 23);

            indices.push_back( 22);
            indices.push_back( 20);
            indices.push_back( 24);

            indices.push_back( 18);
            indices.push_back( 21);
            indices.push_back( 23);

            indices.push_back( 17);
            indices.push_back( 14);
            indices.push_back( 15);

            indices.push_back( 23);
            indices.push_back( 5);
            indices.push_back( 24);

            indices.push_back( 4);
            indices.push_back( 5);
            indices.push_back( 15);

            std::shared_ptr<Geometry> geometry = std::make_shared<Geometry>(indices);
            geometry->set( "vertex", new Buffer<Vec3>( vertices, BufferType::ArrayBuffer) );

            return geometry;
      }

}
