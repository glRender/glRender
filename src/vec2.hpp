#ifndef __VEC2_H__
#define __VEC2_H__

#include <cmath>
#include <iostream>

namespace glRender
{

///////////////////////////////////////////////////////////////////////////////
// 2D vector
///////////////////////////////////////////////////////////////////////////////
struct Vec2
{
    float x;
    float y;

    // ctors
    Vec2() : x(0), y(0) {};
    Vec2(float x, float y) : x(x), y(y) {};

    // utils functions
    void        set(float x, float y);
    float       length() const;                         //
    float       distance(const Vec2& vec) const;     // distance between two vectors
    Vec2&    normalize();                            //
    float       dot(const Vec2& vec) const;          // dot product
    bool        equal(const Vec2& vec, float e) const; // compare with epsilon

    // operators
    Vec2     operator-() const;                      // unary operator (negate)
    Vec2     operator+(const Vec2& rhs) const;    // add rhs
    Vec2     operator-(const Vec2& rhs) const;    // subtract rhs
    Vec2&    operator+=(const Vec2& rhs);         // add rhs and update this object
    Vec2&    operator-=(const Vec2& rhs);         // subtract rhs and update this object
    Vec2     operator*(const float scale) const;     // scale
    Vec2     operator*(const Vec2& rhs) const;    // multiply each element
    Vec2&    operator*=(const float scale);          // scale and update this object
    Vec2&    operator*=(const Vec2& rhs);         // multiply each element and update this object
    Vec2     operator/(const float scale) const;     // inverse scale
    Vec2&    operator/=(const float scale);          // scale and update this object
    bool        operator==(const Vec2& rhs) const;   // exact compare, no epsilon
    bool        operator!=(const Vec2& rhs) const;   // exact compare, no epsilon
    bool        operator<(const Vec2& rhs) const;    // comparison for sort
    float       operator[](int index) const;            // subscript operator v[0], v[1]
    float&      operator[](int index);                  // subscript operator v[0], v[1]

    friend Vec2 operator*(const float a, const Vec2 vec);
    friend std::ostream& operator<<(std::ostream& os, const Vec2& vec);
};

///////////////////////////////////////////////////////////////////////////////
// inline functions for Vec2
///////////////////////////////////////////////////////////////////////////////
inline Vec2 Vec2::operator-() const {
    return Vec2(-x, -y);
}

inline Vec2 Vec2::operator+(const Vec2& rhs) const {
    return Vec2(x+rhs.x, y+rhs.y);
}

inline Vec2 Vec2::operator-(const Vec2& rhs) const {
    return Vec2(x-rhs.x, y-rhs.y);
}

inline Vec2& Vec2::operator+=(const Vec2& rhs) {
    x += rhs.x; y += rhs.y; return *this;
}

inline Vec2& Vec2::operator-=(const Vec2& rhs) {
    x -= rhs.x; y -= rhs.y; return *this;
}

inline Vec2 Vec2::operator*(const float a) const {
    return Vec2(x*a, y*a);
}

inline Vec2 Vec2::operator*(const Vec2& rhs) const {
    return Vec2(x*rhs.x, y*rhs.y);
}

inline Vec2& Vec2::operator*=(const float a) {
    x *= a; y *= a; return *this;
}

inline Vec2& Vec2::operator*=(const Vec2& rhs) {
    x *= rhs.x; y *= rhs.y; return *this;
}

inline Vec2 Vec2::operator/(const float a) const {
    return Vec2(x/a, y/a);
}

inline Vec2& Vec2::operator/=(const float a) {
    x /= a; y /= a; return *this;
}

inline bool Vec2::operator==(const Vec2& rhs) const {
    return (x == rhs.x) && (y == rhs.y);
}

inline bool Vec2::operator!=(const Vec2& rhs) const {
    return (x != rhs.x) || (y != rhs.y);
}

inline bool Vec2::operator<(const Vec2& rhs) const {
    if(x < rhs.x) return true;
    if(x > rhs.x) return false;
    if(y < rhs.y) return true;
    if(y > rhs.y) return false;
    return false;
}

inline float Vec2::operator[](int index) const {
    return (&x)[index];
}

inline float& Vec2::operator[](int index) {
    return (&x)[index];
}

inline void Vec2::set(float x, float y) {
    this->x = x; this->y = y;
}

inline float Vec2::length() const {
    return sqrtf(x*x + y*y);
}

inline float Vec2::distance(const Vec2& vec) const {
    return sqrtf((vec.x-x)*(vec.x-x) + (vec.y-y)*(vec.y-y));
}

inline Vec2& Vec2::normalize() {
    //@@const float EPSILON = 0.000001f;
    float xxyy = x*x + y*y;
    //@@if(xxyy < EPSILON)
    //@@    return *this;

    //float invLength = invSqrt(xxyy);
    float invLength = 1.0f / sqrtf(xxyy);
    x *= invLength;
    y *= invLength;
    return *this;
}

inline float Vec2::dot(const Vec2& rhs) const {
    return (x*rhs.x + y*rhs.y);
}

inline bool Vec2::equal(const Vec2& rhs, float epsilon) const {
    return fabs(x - rhs.x) < epsilon && fabs(y - rhs.y) < epsilon;
}

inline Vec2 operator*(const float a, const Vec2 vec) {
    return Vec2(a*vec.x, a*vec.y);
}

inline std::ostream& operator<<(std::ostream& os, const Vec2& vec) {
    os << "(" << vec.x << ", " << vec.y << ")";
    return os;
}
// END OF VECTOR2 /////////////////////////////////////////////////////////////

    
}

#endif /* __VEC2_H__ */