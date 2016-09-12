#ifndef __VEC3_H__		
#define __VEC3_H__

#include <iostream>
#include <cmath>

#include "opengl.h"

namespace glRender
{

///////////////////////////////////////////////////////////////////////////////
// 3D vector
///////////////////////////////////////////////////////////////////////////////
struct Vec3
{
    float x;
    float y;
    float z;

    // ctors
    Vec3() : x(0), y(0), z(0) {};
    Vec3(float x, float y, float z) : x(x), y(y), z(z) {};

    // utils functions
    void        set(float x, float y, float z);
    float       length() const;                         //
    float       distance(const Vec3& vec) const;     // distance between two vectors
    Vec3&    normalize();                            //
    float       dot(const Vec3& vec) const;          // dot product
    Vec3     cross(const Vec3& vec) const;        // cross product
    bool        equal(const Vec3& vec, float e) const; // compare with epsilon

    // operators
    Vec3     operator-() const;                      // unary operator (negate)
    Vec3     operator+(const Vec3& rhs) const;    // add rhs
    Vec3     operator-(const Vec3& rhs) const;    // subtract rhs
    Vec3&    operator+=(const Vec3& rhs);         // add rhs and update this object
    Vec3&    operator-=(const Vec3& rhs);         // subtract rhs and update this object
    Vec3     operator*(const float scale) const;     // scale
    Vec3     operator*(const Vec3& rhs) const;    // multiplay each element
    Vec3&    operator*=(const float scale);          // scale and update this object
    Vec3&    operator*=(const Vec3& rhs);         // product each element and update this object
    Vec3     operator/(const float scale) const;     // inverse scale
    Vec3&    operator/=(const float scale);          // scale and update this object
    bool        operator==(const Vec3& rhs) const;   // exact compare, no epsilon
    bool        operator!=(const Vec3& rhs) const;   // exact compare, no epsilon
    bool        operator<(const Vec3& rhs) const;    // comparison for sort
    float       operator[](int index) const;            // subscript operator v[0], v[1]
    float&      operator[](int index);                  // subscript operator v[0], v[1]

    static Vec3 AXE_X() { return Vec3(1.0, 0.0, 0.0); };
    static Vec3 AXE_Y() { return Vec3(0.0, 1.0, 0.0); };
    static Vec3 AXE_Z() { return Vec3(0.0, 0.0, 1.0); };

    friend Vec3 operator*(const float a, const Vec3 vec);
    friend std::ostream& operator<<(std::ostream& os, const Vec3& vec);
};

inline Vec3 Vec3::operator-() const {
    return Vec3(-x, -y, -z);
}

inline Vec3 Vec3::operator+(const Vec3& rhs) const {
    return Vec3(x+rhs.x, y+rhs.y, z+rhs.z);
}

inline Vec3 Vec3::operator-(const Vec3& rhs) const {
    return Vec3(x-rhs.x, y-rhs.y, z-rhs.z);
}

inline Vec3& Vec3::operator+=(const Vec3& rhs) {
    x += rhs.x; y += rhs.y; z += rhs.z; return *this;
}

inline Vec3& Vec3::operator-=(const Vec3& rhs) {
    x -= rhs.x; y -= rhs.y; z -= rhs.z; return *this;
}

inline Vec3 Vec3::operator*(const GLfloat a) const {
    return Vec3(x*a, y*a, z*a);
}

inline Vec3 Vec3::operator*(const Vec3& rhs) const {
    return Vec3(x*rhs.x, y*rhs.y, z*rhs.z);
}

inline Vec3& Vec3::operator*=(const GLfloat a) {
    x *= a; y *= a; z *= a; return *this;
}

inline Vec3& Vec3::operator*=(const Vec3& rhs) {
    x *= rhs.x; y *= rhs.y; z *= rhs.z; return *this;
}

inline Vec3 Vec3::operator/(const GLfloat a) const {
    return Vec3(x/a, y/a, z/a);
}

inline Vec3& Vec3::operator/=(const GLfloat a) {
    x /= a; y /= a; z /= a; return *this;
}

inline bool Vec3::operator==(const Vec3& rhs) const {
    return (x == rhs.x) && (y == rhs.y) && (z == rhs.z);
}

inline bool Vec3::operator!=(const Vec3& rhs) const {
    return (x != rhs.x) || (y != rhs.y) || (z != rhs.z);
}

inline bool Vec3::operator<(const Vec3& rhs) const {
    if(x < rhs.x) return true;
    if(x > rhs.x) return false;
    if(y < rhs.y) return true;
    if(y > rhs.y) return false;
    if(z < rhs.z) return true;
    if(z > rhs.z) return false;
    return false;
}

inline GLfloat Vec3::operator[](GLint index) const {
    return (&x)[index];
}

inline GLfloat& Vec3::operator[](GLint index) {
    return (&x)[index];
}

inline void Vec3::set(GLfloat x, GLfloat y, GLfloat z) {
    this->x = x; this->y = y; this->z = z;
}

inline GLfloat Vec3::length() const {
    return sqrtf(x*x + y*y + z*z);
}

inline GLfloat Vec3::distance(const Vec3& vec) const {
    return sqrtf((vec.x-x)*(vec.x-x) + (vec.y-y)*(vec.y-y) + (vec.z-z)*(vec.z-z));
}

inline Vec3& Vec3::normalize() {
    const GLfloat EPSILON = 0.000001f;
    GLfloat xxyyzz = x*x + y*y + z*z;
    if(xxyyzz < EPSILON)
        return *this; // do nothing if it is ~zero vector

    //GLfloat invLength = invSqrt(xxyyzz);
    GLfloat invLength = 1.0f / sqrtf(xxyyzz);
    x *= invLength;
    y *= invLength;
    z *= invLength;
    return *this;
}

inline GLfloat Vec3::dot(const Vec3& rhs) const {
    return (x*rhs.x + y*rhs.y + z*rhs.z);
}

inline Vec3 Vec3::cross(const Vec3& rhs) const {
    return Vec3(y*rhs.z - z*rhs.y, z*rhs.x - x*rhs.z, x*rhs.y - y*rhs.x);
}

inline bool Vec3::equal(const Vec3& rhs, GLfloat epsilon) const {
    return fabs(x - rhs.x) < epsilon && fabs(y - rhs.y) < epsilon && fabs(z - rhs.z) < epsilon;
}

inline Vec3 operator*(const GLfloat a, const Vec3 vec) {
    return Vec3(a*vec.x, a*vec.y, a*vec.z);
}

inline std::ostream& operator<<(std::ostream& os, const Vec3& vec) {
    os << "(" << vec.x << ", " << vec.y << ", " << vec.z << ")";
    return os;
}
    
}

#endif /* __VEC3_H__ */
