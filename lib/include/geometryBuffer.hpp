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
    virtual uint size() = 0;
    virtual uint memorySize() = 0;
    virtual uint id() = 0;
    virtual void bind() = 0;
    virtual void unbind() = 0;
};

template<typename T>
class Buffer : public AbstractBuffer
{
public:
    Buffer(const std::vector<T> & data, int type);
    ~Buffer();

    uint size();
    uint memorySize();
    uint id();
    void bind();
    void unbind();

private:
    uint m_id;
    std::vector<T> m_data;
    int m_type;
};

}

#endif /* __GEOMETRY_BUFFER__ */
