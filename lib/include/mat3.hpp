#ifndef __MAT3_H__      
#define __MAT3_H__

#include <iostream>
#include <iomanip>

#include "vec2.hpp"
#include "vec3.hpp"
#include "vec4.hpp"

namespace glRender
{

///////////////////////////////////////////////////////////////////////////
// 3x3 matrix
///////////////////////////////////////////////////////////////////////////
class Mat3
{
public:
    // constructors
    Mat3();  // init with identity
    Mat3(const float src[9]);
    Mat3(float m0, float m1, float m2,              // 1st column
            float m3, float m4, float m5,           // 2nd column
            float m6, float m7, float m8);          // 3rd column

    void        set(const float src[9]);
    void        set(float m0, float m1, float m2,   // 1st column
                    float m3, float m4, float m5,   // 2nd column
                    float m6, float m7, float m8);  // 3rd column
    void        setRow(int index, const float row[3]);
    void        setRow(int index, const Vec3& v);
    void        setColumn(int index, const float col[3]);
    void        setColumn(int index, const Vec3& v);

    const float* get() const;
    float       getDeterminant();

    Mat3&    identity();
    Mat3&    transpose();                            // transpose itself and return reference
    Mat3&    invert();

    // operators
    Mat3     operator+(const Mat3& rhs) const;    // add rhs
    Mat3     operator-(const Mat3& rhs) const;    // subtract rhs
    Mat3&    operator+=(const Mat3& rhs);         // add rhs and update this object
    Mat3&    operator-=(const Mat3& rhs);         // subtract rhs and update this object
    Vec3     operator*(const Vec3& rhs) const;    // multiplication: v' = M * v
    Mat3     operator*(const Mat3& rhs) const;    // multiplication: M3 = M1 * M2
    Mat3&    operator*=(const Mat3& rhs);         // multiplication: M1' = M1 * M2
    bool        operator==(const Mat3& rhs) const;   // exact compare, no epsilon
    bool        operator!=(const Mat3& rhs) const;   // exact compare, no epsilon
    float       operator[](int index) const;            // subscript operator v[0], v[1]
    float&      operator[](int index);                  // subscript operator v[0], v[1]

    friend Mat3 operator-(const Mat3& m);                     // unary operator (-)
    friend Mat3 operator*(float scalar, const Mat3& m);       // pre-multiplication
    friend Vec3 operator*(const Vec3& vec, const Mat3& m); // pre-multiplication
    friend std::ostream& operator<<(std::ostream& os, const Mat3& m);

protected:

private:
    float m[9];

};

///////////////////////////////////////////////////////////////////////////
// inline functions for Mat3
///////////////////////////////////////////////////////////////////////////
inline Mat3::Mat3()
{
    // initially identity matrix
    identity();
}



inline Mat3::Mat3(const float src[9])
{
    set(src);
}



inline Mat3::Mat3(float m0, float m1, float m2,
                        float m3, float m4, float m5,
                        float m6, float m7, float m8)
{
    set(m0, m1, m2,  m3, m4, m5,  m6, m7, m8);
}



inline void Mat3::set(const float src[9])
{
    m[0] = src[0];  m[1] = src[1];  m[2] = src[2];
    m[3] = src[3];  m[4] = src[4];  m[5] = src[5];
    m[6] = src[6];  m[7] = src[7];  m[8] = src[8];
}



inline void Mat3::set(float m0, float m1, float m2,
                         float m3, float m4, float m5,
                         float m6, float m7, float m8)
{
    m[0] = m0;  m[1] = m1;  m[2] = m2;
    m[3] = m3;  m[4] = m4;  m[5] = m5;
    m[6] = m6;  m[7] = m7;  m[8] = m8;
}



inline void Mat3::setRow(int index, const float row[3])
{
    m[index] = row[0];  m[index + 3] = row[1];  m[index + 6] = row[2];
}



inline void Mat3::setRow(int index, const Vec3& v)
{
    m[index] = v.x;  m[index + 3] = v.y;  m[index + 6] = v.z;
}



inline void Mat3::setColumn(int index, const float col[3])
{
    m[index*3] = col[0];  m[index*3 + 1] = col[1];  m[index*3 + 2] = col[2];
}



inline void Mat3::setColumn(int index, const Vec3& v)
{
    m[index*3] = v.x;  m[index*3 + 1] = v.y;  m[index*3 + 2] = v.z;
}



inline const float* Mat3::get() const
{
    return m;
}



inline Mat3& Mat3::identity()
{
    m[0] = m[4] = m[8] = 1.0f;
    m[1] = m[2] = m[3] = m[5] = m[6] = m[7] = 0.0f;
    return *this;
}



inline Mat3 Mat3::operator+(const Mat3& rhs) const
{
    return Mat3(m[0]+rhs[0], m[1]+rhs[1], m[2]+rhs[2],
                   m[3]+rhs[3], m[4]+rhs[4], m[5]+rhs[5],
                   m[6]+rhs[6], m[7]+rhs[7], m[8]+rhs[8]);
}



inline Mat3 Mat3::operator-(const Mat3& rhs) const
{
    return Mat3(m[0]-rhs[0], m[1]-rhs[1], m[2]-rhs[2],
                   m[3]-rhs[3], m[4]-rhs[4], m[5]-rhs[5],
                   m[6]-rhs[6], m[7]-rhs[7], m[8]-rhs[8]);
}



inline Mat3& Mat3::operator+=(const Mat3& rhs)
{
    m[0] += rhs[0];  m[1] += rhs[1];  m[2] += rhs[2];
    m[3] += rhs[3];  m[4] += rhs[4];  m[5] += rhs[5];
    m[6] += rhs[6];  m[7] += rhs[7];  m[8] += rhs[8];
    return *this;
}



inline Mat3& Mat3::operator-=(const Mat3& rhs)
{
    m[0] -= rhs[0];  m[1] -= rhs[1];  m[2] -= rhs[2];
    m[3] -= rhs[3];  m[4] -= rhs[4];  m[5] -= rhs[5];
    m[6] -= rhs[6];  m[7] -= rhs[7];  m[8] -= rhs[8];
    return *this;
}



inline Vec3 Mat3::operator*(const Vec3& rhs) const
{
    return Vec3(m[0]*rhs.x + m[3]*rhs.y + m[6]*rhs.z,
                   m[1]*rhs.x + m[4]*rhs.y + m[7]*rhs.z,
                   m[2]*rhs.x + m[5]*rhs.y + m[8]*rhs.z);
}



inline Mat3 Mat3::operator*(const Mat3& rhs) const
{
    return Mat3(m[0]*rhs[0] + m[3]*rhs[1] + m[6]*rhs[2],  m[1]*rhs[0] + m[4]*rhs[1] + m[7]*rhs[2],  m[2]*rhs[0] + m[5]*rhs[1] + m[8]*rhs[2],
                   m[0]*rhs[3] + m[3]*rhs[4] + m[6]*rhs[5],  m[1]*rhs[3] + m[4]*rhs[4] + m[7]*rhs[5],  m[2]*rhs[3] + m[5]*rhs[4] + m[8]*rhs[5],
                   m[0]*rhs[6] + m[3]*rhs[7] + m[6]*rhs[8],  m[1]*rhs[6] + m[4]*rhs[7] + m[7]*rhs[8],  m[2]*rhs[6] + m[5]*rhs[7] + m[8]*rhs[8]);
}



inline Mat3& Mat3::operator*=(const Mat3& rhs)
{
    *this = *this * rhs;
    return *this;
}



inline bool Mat3::operator==(const Mat3& rhs) const
{
    return (m[0] == rhs[0]) && (m[1] == rhs[1]) && (m[2] == rhs[2]) &&
           (m[3] == rhs[3]) && (m[4] == rhs[4]) && (m[5] == rhs[5]) &&
           (m[6] == rhs[6]) && (m[7] == rhs[7]) && (m[8] == rhs[8]);
}



inline bool Mat3::operator!=(const Mat3& rhs) const
{
    return (m[0] != rhs[0]) || (m[1] != rhs[1]) || (m[2] != rhs[2]) ||
           (m[3] != rhs[3]) || (m[4] != rhs[4]) || (m[5] != rhs[5]) ||
           (m[6] != rhs[6]) || (m[7] != rhs[7]) || (m[8] != rhs[8]);
}



inline float Mat3::operator[](int index) const
{
    return m[index];
}



inline float& Mat3::operator[](int index)
{
    return m[index];
}



inline Mat3 operator-(const Mat3& rhs)
{
    return Mat3(-rhs[0], -rhs[1], -rhs[2], -rhs[3], -rhs[4], -rhs[5], -rhs[6], -rhs[7], -rhs[8]);
}



inline Mat3 operator*(float s, const Mat3& rhs)
{
    return Mat3(s*rhs[0], s*rhs[1], s*rhs[2], s*rhs[3], s*rhs[4], s*rhs[5], s*rhs[6], s*rhs[7], s*rhs[8]);
}



inline Vec3 operator*(const Vec3& v, const Mat3& m)
{
    return Vec3(v.x*m[0] + v.y*m[1] + v.z*m[2],  v.x*m[3] + v.y*m[4] + v.z*m[5],  v.x*m[6] + v.y*m[7] + v.z*m[8]);
}



inline std::ostream& operator<<(std::ostream& os, const Mat3& m)
{
    os << std::fixed << std::setprecision(5);
    os << "[" << std::setw(10) << m[0] << " " << std::setw(10) << m[3] << " " << std::setw(10) << m[6] << "]\n"
       << "[" << std::setw(10) << m[1] << " " << std::setw(10) << m[4] << " " << std::setw(10) << m[7] << "]\n"
       << "[" << std::setw(10) << m[2] << " " << std::setw(10) << m[5] << " " << std::setw(10) << m[8] << "]\n";
    os << std::resetiosflags(std::ios_base::fixed | std::ios_base::floatfield);
    return os;
}
// END OF MATRIX3 INLINE //////////////////////////////////////////////////////
    
}


#endif /* __MAT3_H__ */
