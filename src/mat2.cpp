#include "mat2.hpp"

namespace glRender {
const float DEG2RAD = 3.141593f / 180;
const float EPSILON = 0.00001f;

///////////////////////////////////////////////////////////////////////////////
// transpose 2x2 matrix
///////////////////////////////////////////////////////////////////////////////
glRender::Mat2& glRender::Mat2::transpose()
{
    std::swap(m[1],  m[2]);
    return *this;
}



///////////////////////////////////////////////////////////////////////////////
// return the determinant of 2x2 matrix
///////////////////////////////////////////////////////////////////////////////
float glRender::Mat2::getDeterminant()
{
    return m[0] * m[3] - m[1] * m[2];
}



///////////////////////////////////////////////////////////////////////////////
// inverse of 2x2 matrix
// If cannot find inverse, set identity matrix
///////////////////////////////////////////////////////////////////////////////
glRender::Mat2& glRender::Mat2::invert()
{
    float determinant = getDeterminant();
    if(fabs(determinant) <= EPSILON)
    {
        return identity();
    }

    float tmp = m[0];   // copy the first element
    float invDeterminant = 1.0f / determinant;
    m[0] =  invDeterminant * m[3];
    m[1] = -invDeterminant * m[1];
    m[2] = -invDeterminant * m[2];
    m[3] =  invDeterminant * tmp;

    return *this;
}
    
}
