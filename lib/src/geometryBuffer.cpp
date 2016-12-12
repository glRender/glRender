#include "geometryBuffer.hpp"
#include "opengl.h"

//0x8892 GL_ARRAY_BUFFER
//0x8893 GL_ELEMENT_ARRAY_BUFFER

using namespace glRender;

template<typename T>
Buffer<T>::Buffer(const std::vector<T> & data, int type)
    : m_data(data)
    , m_type(type)
{
    if (type == 0x8892)
    {
        glGenBuffers(1, &m_id);
        glBindBuffer(GL_ARRAY_BUFFER, m_id);
        glBufferData(GL_ARRAY_BUFFER, m_data.size() * sizeof(T), m_data.data(), GL_STATIC_DRAW);
    }
    else if (type == 0x8893)
    {
        glGenBuffers(1, &m_id);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_id);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_data.size() * sizeof(T), m_data.data(), GL_STATIC_DRAW);
    }

}

template<typename T>
Buffer<T>::~Buffer()
{
    glDeleteBuffers(1, &m_id);
}

template<typename T>
uint Buffer<T>::size()
{
    return m_data.size();
}

template<typename T>
uint Buffer<T>::memorySize()
{
    return m_data.size() * sizeof(T);
}

template<typename T>
uint Buffer<T>::id()
{
    return m_id;
}

template<typename T>
void Buffer<T>::bind()
{
    glBindBuffer(m_type, m_id);
}

template<typename T>
void Buffer<T>::unbind()
{
    glBindBuffer(m_type , 0);
}

template class Buffer<Vec3>;
template class Buffer<uint>;
template class Buffer<Vec2>;
template class Buffer<float>;
