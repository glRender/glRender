#ifndef __VEC4_H__      
#define __VEC4_H__

#include <iostream>
#include <cmath>

#include "opengl.h"

namespace glRender
{

struct Vec4
{
    float x;
    float y;
    float z;
    float w;

    // ctors
    Vec4() : x(0), y(0), z(0), w(0) {};
    Vec4(float x, float y, float z, float w) : x(x), y(y), z(z), w(w) {};

    // utils functions
    void        set(float x, float y, float z, float w);
    float       length() const;                         //
    float       distance(const Vec4& vec) const;     // distance between two vectors
    Vec4&    normalize();                            //
    float       dot(const Vec4& vec) const;          // dot product
    bool        equal(const Vec4& vec, float e) const; // compare with epsilon

    // operators
    Vec4     operator-() const;                      // unary operator (negate)
    Vec4     operator+(const Vec4& rhs) const;    // add rhs
    Vec4     operator-(const Vec4& rhs) const;    // subtract rhs
    Vec4&    operator+=(const Vec4& rhs);         // add rhs and update this object
    Vec4&    operator-=(const Vec4& rhs);         // subtract rhs and update this object
    Vec4     operator*(const float scale) const;     // scale
    Vec4     operator*(const Vec4& rhs) const;    // multiply each element
    Vec4&    operator*=(const float scale);          // scale and update this object
    Vec4&    operator*=(const Vec4& rhs);         // multiply each element and update this object
    Vec4     operator/(const float scale) const;     // inverse scale
    Vec4&    operator/=(const float scale);          // scale and update this object
    bool        operator==(const Vec4& rhs) const;   // exact compare, no epsilon
    bool        operator!=(const Vec4& rhs) const;   // exact compare, no epsilon
    bool        operator<(const Vec4& rhs) const;    // comparison for sort
    float       operator[](int index) const;            // subscript operator v[0], v[1]
    float&      operator[](int index);                  // subscript operator v[0], v[1]

    friend Vec4 operator*(const float a, const Vec4 vec);
    friend std::ostream& operator<<(std::ostream& os, const Vec4& vec);
};

inline Vec4 Vec4::operator-() const {
    return Vec4(-x, -y, -z, -w);
}

inline Vec4 Vec4::operator+(const Vec4& rhs) const {
    return Vec4(x+rhs.x, y+rhs.y, z+rhs.z, w+rhs.w);
}

inline Vec4 Vec4::operator-(const Vec4& rhs) const {
    return Vec4(x-rhs.x, y-rhs.y, z-rhs.z, w-rhs.w);
}

inline Vec4& Vec4::operator+=(const Vec4& rhs) {
    x += rhs.x; y += rhs.y; z += rhs.z; w += rhs.w; return *this;
}

inline Vec4& Vec4::operator-=(const Vec4& rhs) {
    x -= rhs.x; y -= rhs.y; z -= rhs.z; w -= rhs.w; return *this;
}

inline Vec4 Vec4::operator*(const float a) const {
    return Vec4(x*a, y*a, z*a, w*a);
}

inline Vec4 Vec4::operator*(const Vec4& rhs) const {
    return Vec4(x*rhs.x, y*rhs.y, z*rhs.z, w*rhs.w);
}

inline Vec4& Vec4::operator*=(const float a) {
    x *= a; y *= a; z *= a; w *= a; return *this;
}

inline Vec4& Vec4::operator*=(const Vec4& rhs) {
    x *= rhs.x; y *= rhs.y; z *= rhs.z; w *= rhs.w; return *this;
}

inline Vec4 Vec4::operator/(const float a) const {
    return Vec4(x/a, y/a, z/a, w/a);
}

inline Vec4& Vec4::operator/=(const float a) {
    x /= a; y /= a; z /= a; w /= a; return *this;
}

inline bool Vec4::operator==(const Vec4& rhs) const {
    return (x == rhs.x) && (y == rhs.y) && (z == rhs.z) && (w == rhs.w);
}

inline bool Vec4::operator!=(const Vec4& rhs) const {
    return (x != rhs.x) || (y != rhs.y) || (z != rhs.z) || (w != rhs.w);
}

inline bool Vec4::operator<(const Vec4& rhs) const {
    if(x < rhs.x) return true;
    if(x > rhs.x) return false;
    if(y < rhs.y) return true;
    if(y > rhs.y) return false;
    if(z < rhs.z) return true;
    if(z > rhs.z) return false;
    if(w < rhs.w) return true;
    if(w > rhs.w) return false;
    return false;
}

inline float Vec4::operator[](int index) const {
    return (&x)[index];
}

inline float& Vec4::operator[](int index) {
    return (&x)[index];
}

inline void Vec4::set(float x, float y, float z, float w) {
    this->x = x; this->y = y; this->z = z; this->w = w;
}

inline float Vec4::length() const {
    return sqrtf(x*x + y*y + z*z + w*w);
}

inline float Vec4::distance(const Vec4& vec) const {
    return sqrtf((vec.x-x)*(vec.x-x) + (vec.y-y)*(vec.y-y) + (vec.z-z)*(vec.z-z) + (vec.w-w)*(vec.w-w));
}

inline Vec4& Vec4::normalize() {
    //NOTE: leave w-component untouched
    //@@const float EPSILON = 0.000001f;
    float xxyyzz = x*x + y*y + z*z;
    //@@if(xxyyzz < EPSILON)
    //@@    return *this; // do nothing if it is zero vector

    //float invLength = invSqrt(xxyyzz);
    float invLength = 1.0f / sqrtf(xxyyzz);
    x *= invLength;
    y *= invLength;
    z *= invLength;
    return *this;
}

inline float Vec4::dot(const Vec4& rhs) const {
    return (x*rhs.x + y*rhs.y + z*rhs.z + w*rhs.w);
}

inline bool Vec4::equal(const Vec4& rhs, float epsilon) const {
    return fabs(x - rhs.x) < epsilon && fabs(y - rhs.y) < epsilon &&
           fabs(z - rhs.z) < epsilon && fabs(w - rhs.w) < epsilon;
}

inline Vec4 operator*(const float a, const Vec4 vec) {
    return Vec4(a*vec.x, a*vec.y, a*vec.z, a*vec.w);
}

inline std::ostream& operator<<(std::ostream& os, const Vec4& vec) {
    os << "(" << vec.x << ", " << vec.y << ", " << vec.z << ", " << vec.w << ")";
    return os;
}

}

#endif /* __VEC4_H__ */
