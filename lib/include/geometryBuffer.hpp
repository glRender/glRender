#ifndef __GEOMETRY_BUFFER__
#define __GEOMETRY_BUFFER__

#include "base.h"

#include "vec3.hpp"
#include "vec4.hpp"
#include "mat4.hpp"

namespace glRender
{

class AbstractBuffer
{
public:
    virtual ~AbstractBuffer()
    {

    }

    virtual uint32_t size() = 0;
    virtual uint32_t memorySize() = 0;
    virtual uint32_t id() = 0;
    virtual void bind() = 0;
    virtual void unbind() = 0;
};

enum class BufferType
{
    ArrayBuffer,       /*GL_ARRAY_BUFFER*/
    ElementArrayBuffer /*GL_ELEMENT_ARRAY_BUFFER*/
};

template<typename T>
class Buffer : public AbstractBuffer
{
public:
    Buffer(const std::vector<T> & data, BufferType type);
    ~Buffer();

    uint32_t size();
    uint32_t memorySize();
    uint32_t id();
    void bind();
    void unbind();
    void rewrite(const uint32_t from, const std::vector<T> & data);
    void rewrite(const uint32_t index, const T & element);

private:
    uint32_t m_id;
    std::vector<T> m_data;
    uint32_t m_type;
};

}

#endif /* __GEOMETRY_BUFFER__ */
