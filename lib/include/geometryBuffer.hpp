#ifndef __GEOMETRY_BUFFER__
#define __GEOMETRY_BUFFER__

#include "base.h"

#include "vec3.hpp"
#include "vec4.hpp"
#include "mat4.hpp"

namespace glRender
{

class Buffer
{
public:
    ~Buffer()
    {
        glDeleteBuffers(1, &m_id);
    }

    virtual const int size() = 0;
    virtual const int memorySize() = 0;

    inline const GLuint id()
    {
        return m_id;
    }

protected:
    GLuint m_id;

};

class AttributeBuffer : public Buffer
{
public:
    virtual const int size() = 0;
    virtual const int memorySize() = 0;

    inline virtual void bind()
    {
        glBindBuffer ( GL_ARRAY_BUFFER, m_id );
    }

    inline virtual void unbind()
    {
        glBindBuffer ( GL_ARRAY_BUFFER, 0 );
    }

};

template<typename T>
class AtributeBufferTemplate : public AttributeBuffer
{
public:
    AtributeBufferTemplate(std::vector<T> & data)
        : m_data(data)
    {
        glGenBuffers(1, &m_id);
        glBindBuffer(GL_ARRAY_BUFFER, m_id);
        glBufferData(GL_ARRAY_BUFFER, m_data.size() * sizeof(T), m_data.data(), GL_STATIC_DRAW);
    };

    const int size() override
    {
        return m_data.size();
    }

    const int memorySize() override
    {
        return m_data.size() * sizeof(T);
    }

protected:
    std::vector<T> m_data;

};

class IndicesBuffer : public Buffer
{
public:
    virtual const int size() = 0;
    virtual const int memorySize() = 0;

};

template<typename T>
class IndicesBufferTemplate : public IndicesBuffer
{
public:
    IndicesBufferTemplate(const std::vector<T> & data)
        : m_data(data)
    {
        glGenBuffers(1, &m_id);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_id);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_data.size() * sizeof(uint), m_data.data(), GL_STATIC_DRAW);
    };

    virtual const int size()
    {
        return m_data.size();
    }

    virtual const int memorySize()
    {
        return m_data.size() * sizeof(uint);
    }

protected:
    std::vector<T> m_data;

};

}

#endif /* __GEOMETRY_BUFFER__ */
