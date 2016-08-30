#ifndef __MAT2_H__      
#define __MAT2_H__

#include <iostream>
#include <iomanip>

#include "vec2.hpp"
#include "vec3.hpp"
#include "vec4.hpp"

namespace glRender
{
class Mat2
{
public:
    // constructors
    Mat2();  // init with identity
    Mat2(const float src[4]);
    Mat2(float m0, float m1, float m2, float m3);

    void        set(const float src[4]);
    void        set(float m0, float m1, float m2, float m3);
    void        setRow(int index, const float row[2]);
    void        setRow(int index, const Vec2& v);
    void        setColumn(int index, const float col[2]);
    void        setColumn(int index, const Vec2& v);

    const float* get() const;
    float       getDeterminant();

    Mat2&    identity();
    Mat2&    transpose();                         // transpose itself and return reference
    Mat2&    invert();

    // operators
    Mat2     operator+(const Mat2& rhs) const;    // add rhs
    Mat2     operator-(const Mat2& rhs) const;    // subtract rhs
    Mat2&    operator+=(const Mat2& rhs);         // add rhs and update this object
    Mat2&    operator-=(const Mat2& rhs);         // subtract rhs and update this object
    Vec2     operator*(const Vec2& rhs) const;    // multiplication: v' = M * v
    Mat2     operator*(const Mat2& rhs) const;    // multiplication: M3 = M1 * M2
    Mat2&    operator*=(const Mat2& rhs);         // multiplication: M1' = M1 * M2
    bool        operator==(const Mat2& rhs) const;   // exact compare, no epsilon
    bool        operator!=(const Mat2& rhs) const;   // exact compare, no epsilon
    float       operator[](int index) const;            // subscript operator v[0], v[1]
    float&      operator[](int index);                  // subscript operator v[0], v[1]

    friend Mat2 operator-(const Mat2& m);                     // unary operator (-)
    friend Mat2 operator*(float scalar, const Mat2& m);       // pre-multiplication
    friend Vec2 operator*(const Vec2& vec, const Mat2& m); // pre-multiplication
    friend std::ostream& operator<<(std::ostream& os, const Mat2& m);

protected:

private:
    float m[4];

};

///////////////////////////////////////////////////////////////////////////
// inline functions for Mat2
///////////////////////////////////////////////////////////////////////////
inline Mat2::Mat2()
{
    // initially identity matrix
    identity();
}



inline Mat2::Mat2(const float src[4])
{
    set(src);
}



inline Mat2::Mat2(float m0, float m1, float m2, float m3)
{
    set(m0, m1, m2, m3);
}



inline void Mat2::set(const float src[4])
{
    m[0] = src[0];  m[1] = src[1];  m[2] = src[2];  m[3] = src[3];
}



inline void Mat2::set(float m0, float m1, float m2, float m3)
{
    m[0]= m0;  m[1] = m1;  m[2] = m2;  m[3]= m3;
}



inline void Mat2::setRow(int index, const float row[2])
{
    m[index] = row[0];  m[index + 2] = row[1];
}



inline void Mat2::setRow(int index, const Vec2& v)
{
    m[index] = v.x;  m[index + 2] = v.y;
}



inline void Mat2::setColumn(int index, const float col[2])
{
    m[index*2] = col[0];  m[index*2 + 1] = col[1];
}



inline void Mat2::setColumn(int index, const Vec2& v)
{
    m[index*2] = v.x;  m[index*2 + 1] = v.y;
}



inline const float* Mat2::get() const
{
    return m;
}



inline Mat2& Mat2::identity()
{
    m[0] = m[3] = 1.0f;
    m[1] = m[2] = 0.0f;
    return *this;
}



inline Mat2 Mat2::operator+(const Mat2& rhs) const
{
    return Mat2(m[0]+rhs[0], m[1]+rhs[1], m[2]+rhs[2], m[3]+rhs[3]);
}



inline Mat2 Mat2::operator-(const Mat2& rhs) const
{
    return Mat2(m[0]-rhs[0], m[1]-rhs[1], m[2]-rhs[2], m[3]-rhs[3]);
}



inline Mat2& Mat2::operator+=(const Mat2& rhs)
{
    m[0] += rhs[0];  m[1] += rhs[1];  m[2] += rhs[2];  m[3] += rhs[3];
    return *this;
}



inline Mat2& Mat2::operator-=(const Mat2& rhs)
{
    m[0] -= rhs[0];  m[1] -= rhs[1];  m[2] -= rhs[2];  m[3] -= rhs[3];
    return *this;
}



inline Vec2 Mat2::operator*(const Vec2& rhs) const
{
    return Vec2(m[0]*rhs.x + m[2]*rhs.y,  m[1]*rhs.x + m[3]*rhs.y);
}



inline Mat2 Mat2::operator*(const Mat2& rhs) const
{
    return Mat2(m[0]*rhs[0] + m[2]*rhs[1],  m[1]*rhs[0] + m[3]*rhs[1],
                   m[0]*rhs[2] + m[2]*rhs[3],  m[1]*rhs[2] + m[3]*rhs[3]);
}



inline Mat2& Mat2::operator*=(const Mat2& rhs)
{
    *this = *this * rhs;
    return *this;
}



inline bool Mat2::operator==(const Mat2& rhs) const
{
    return (m[0] == rhs[0]) && (m[1] == rhs[1]) && (m[2] == rhs[2]) && (m[3] == rhs[3]);
}



inline bool Mat2::operator!=(const Mat2& rhs) const
{
    return (m[0] != rhs[0]) || (m[1] != rhs[1]) || (m[2] != rhs[2]) || (m[3] != rhs[3]);
}



inline float Mat2::operator[](int index) const
{
    return m[index];
}



inline float& Mat2::operator[](int index)
{
    return m[index];
}



inline Mat2 operator-(const Mat2& rhs)
{
    return Mat2(-rhs[0], -rhs[1], -rhs[2], -rhs[3]);
}



inline Mat2 operator*(float s, const Mat2& rhs)
{
    return Mat2(s*rhs[0], s*rhs[1], s*rhs[2], s*rhs[3]);
}



inline Vec2 operator*(const Vec2& v, const Mat2& rhs)
{
    return Vec2(v.x*rhs[0] + v.y*rhs[1],  v.x*rhs[2] + v.y*rhs[3]);
}



inline std::ostream& operator<<(std::ostream& os, const Mat2& m)
{
    os << std::fixed << std::setprecision(5);
    os << "[" << std::setw(10) << m[0] << " " << std::setw(10) << m[2] << "]\n"
       << "[" << std::setw(10) << m[1] << " " << std::setw(10) << m[3] << "]\n";
    os << std::resetiosflags(std::ios_base::fixed | std::ios_base::floatfield);
    return os;
}
// END OF MATRIX2 INLINE //////////////////////////////////////////////////////
    
}


#endif /* __MAT2_H__ */
