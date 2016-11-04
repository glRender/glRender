#ifndef __GEOMETRY_H__		
#define __GEOMETRY_H__

#include "base.h"

#include "attribute.h"
#include "geometryBuffer.hpp"

namespace glRender
{

class Geometry
{

public:
    void set(const char * uniformName, GeometryBuffer * geometryBuffer);

    GeometryBuffer * get(const char * name);
    GeometryBuffer * get(const int index);

    bool has(const char * name);
    bool has(const int index);

    inline uint size()
    {
        return m_geometryBuffers.size();
    }

    inline void bufferAll()
    {
        // buffer all geometry buffers
        for(int i=0; i < size(); ++i)
        {
            GeometryBuffer * buffer =  get(i);
            if (buffer != nullptr)
            {
                buffer->bufferData();
            }
        }
    }

    Geometry();
    ~Geometry();

protected:
    std::map<std::string, GeometryBuffer*> m_geometryBuffers;

};

}

#endif /* __GEOMETRY_H__ */
