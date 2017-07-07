#include "positionable.hpp"

namespace glRender {

void Positionable::setOrigin(const Vec3 & pos)
{
    Vec3 delta = origin() - pos;
    delta *= -1;
    translate( delta );
}

Mat4 &Positionable::transforms()
{
    return m_localMatrix;
}

void Positionable::setOrigin(const float x, const float y, const float z)
{
    setOrigin( Vec3(x, y, z) );
}

const Vec3 Positionable::origin() const
{
//    Vec4 position = m_transformationMatrix * Vec4(0,0,0,1);
    Vec4 position = m_localMatrix * Vec4(0,0,0,1);
    Vec3 resultPosition(position.x, position.y, position.z);
    return resultPosition;
}

void Positionable::translate(const float x, const float y, const float z)
{
//    m_transformationMatrix = m_transformationMatrix.translate(x, y, z);
    setLocalMatrix( m_localMatrix.translate(x, y, z) );
}

void Positionable::translate(const Vec3 & pos)
{
    Positionable::translate(pos.x, pos.y, pos.z);
}

void Positionable::rotate(const float value, const float x, const float y, const float z)
{
//    m_transformationMatrix = m_transformationMatrix.rotate( value, x, y, z );

    setLocalMatrix( m_localMatrix.rotate(value, x, y, z) );
    m_modelRotationMatrix     = m_modelRotationMatrix.rotate( value, x, y, z );

}

void Positionable::rotate(const float value, const Vec3 & v)
{
    Positionable::rotate( value, v.x, v.y, v.z );
}

//void Positionable::setTransformationMatrix(const Mat4 & matrix)
//{
//    m_transformationMatrix = matrix;
//}

//const Mat4& Positionable::transformationMatrix() const
//{
//    return m_transformationMatrix;
//}

const Vec3 Positionable::up() const
{
    Vec4 v = m_modelRotationMatrix * m_up;
    Vec3 up(v.x, v.y, v.z);
    return up;
}

const Vec3 Positionable::front() const
{
    Vec4 v = m_modelRotationMatrix * m_front;
    Vec3 front(v.x, v.y, v.z);
    return front;
}

const Vec3 Positionable::right() const
{   
    Vec4 v = m_modelRotationMatrix * m_right;
    Vec3 right(v.x, v.y, v.z);
    return right;

}

const Vec3 Positionable::upOrig() const
{
    Vec3 up(m_up.x, m_up.y, m_up.z);
    return up;
}

const Vec3 Positionable::frontOrig() const
{
    Vec3 front(m_front.x, m_front.y, m_front.z);
    return front;
}

const Vec3 Positionable::rightOrig() const
{
    Vec3 right(m_right.x, m_right.y, m_right.z);
    return right;

}

void Positionable::setLocalMatrix(const Mat4 & m)
{
    m_localMatrix = m;
    m_globalMatrix = m_localMatrix * m_parentsMatrix;
}

void Positionable::setParentsMatrix(const Mat4 & m)
{
    m_parentsMatrix = m;
    m_globalMatrix = m_localMatrix * m_parentsMatrix;
}

void Positionable::setGlobalMatrix(const Mat4 & m)
{
    m_globalMatrix = m;
}

const Mat4 & Positionable::localMatrix() const
{
    return m_localMatrix;
}

const Mat4 &Positionable::parentsMatrix() const
{
    return m_parentsMatrix;
}

const Mat4 & Positionable::globalMatrix() const
{
    return m_globalMatrix;
}

}
