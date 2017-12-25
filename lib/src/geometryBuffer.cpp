#include "geometryBuffer.hpp"

#include "opengl.h"
#include "vec2.hpp"
#include "vec3.hpp"

//0x8892 GL_ARRAY_BUFFER
//0x8893 GL_ELEMENT_ARRAY_BUFFER

using namespace glRender;

std::map<BufferType, GLenum> bufferTypeToGlenum =
{
    {BufferType::ArrayBuffer, GL_ARRAY_BUFFER},
    {BufferType::ElementArrayBuffer, GL_ELEMENT_ARRAY_BUFFER}
};

template<typename T>
Buffer<T>::Buffer(const std::vector<T> & data, BufferType type)
    : m_data(data)
    , m_type(bufferTypeToGlenum[type])
{
    glGenBuffers(1, &m_id);
    glBindBuffer(m_type, m_id);
    glBufferData(m_type, m_data.size() * sizeof(T), m_data.data(), GL_STATIC_DRAW);
}

template<typename T>
Buffer<T>::~Buffer()
{
    glDeleteBuffers(1, &m_id);
}

template<typename T>
uint32_t Buffer<T>::size()
{
    return m_data.size();
}

template<typename T>
uint32_t Buffer<T>::memorySize()
{
    return m_data.size() * sizeof(T);
}

template<typename T>
uint32_t Buffer<T>::id()
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

template<typename T>
void Buffer<T>::rewrite(const uint32_t from, const std::vector<T> &data)
{
    glBindBuffer(m_type, m_id);
    glBufferSubData(m_type, from * sizeof(T), data.size() * sizeof(T), data.data());
    glBindBuffer(m_type , 0);
}

template<typename T>
void Buffer<T>::rewrite(const uint32_t index, const T & element)
{
    glBindBuffer(m_type, m_id);
    glBufferSubData(m_type, index * sizeof(T), sizeof(T), &element);
    glBindBuffer(m_type , 0);
}

template class Buffer<Vec3>;
template class Buffer<uint32_t>;
template class Buffer<Vec2>;
template class Buffer<float>;
