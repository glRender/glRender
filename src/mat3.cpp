#include "mat3.hpp"

namespace glRender {
const float DEG2RAD = 3.141593f / 180;
const float EPSILON = 0.00001f;

///////////////////////////////////////////////////////////////////////////////
// transpose 3x3 matrix
///////////////////////////////////////////////////////////////////////////////
Mat3& Mat3::transpose()
{
    std::swap(m[1],  m[3]);
    std::swap(m[2],  m[6]);
    std::swap(m[5],  m[7]);

    return *this;
}



///////////////////////////////////////////////////////////////////////////////
// return determinant of 3x3 matrix
///////////////////////////////////////////////////////////////////////////////
float Mat3::getDeterminant()
{
    return m[0] * (m[4] * m[8] - m[5] * m[7]) -
           m[1] * (m[3] * m[8] - m[5] * m[6]) +
           m[2] * (m[3] * m[7] - m[4] * m[6]);
}



///////////////////////////////////////////////////////////////////////////////
// inverse 3x3 matrix
// If cannot find inverse, set identity matrix
///////////////////////////////////////////////////////////////////////////////
Mat3& Mat3::invert()
{
    float determinant, invDeterminant;
    float tmp[9];

    tmp[0] = m[4] * m[8] - m[5] * m[7];
    tmp[1] = m[2] * m[7] - m[1] * m[8];
    tmp[2] = m[1] * m[5] - m[2] * m[4];
    tmp[3] = m[5] * m[6] - m[3] * m[8];
    tmp[4] = m[0] * m[8] - m[2] * m[6];
    tmp[5] = m[2] * m[3] - m[0] * m[5];
    tmp[6] = m[3] * m[7] - m[4] * m[6];
    tmp[7] = m[1] * m[6] - m[0] * m[7];
    tmp[8] = m[0] * m[4] - m[1] * m[3];

    // check determinant if it is 0
    determinant = m[0] * tmp[0] + m[1] * tmp[3] + m[2] * tmp[6];
    if(fabs(determinant) <= EPSILON)
    {
        return identity(); // cannot inverse, make it idenety matrix
    }

    // divide by the determinant
    invDeterminant = 1.0f / determinant;
    m[0] = invDeterminant * tmp[0];
    m[1] = invDeterminant * tmp[1];
    m[2] = invDeterminant * tmp[2];
    m[3] = invDeterminant * tmp[3];
    m[4] = invDeterminant * tmp[4];
    m[5] = invDeterminant * tmp[5];
    m[6] = invDeterminant * tmp[6];
    m[7] = invDeterminant * tmp[7];
    m[8] = invDeterminant * tmp[8];

    return *this;
}
    
}
