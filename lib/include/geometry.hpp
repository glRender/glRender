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
    Geometry();
    Geometry(std::vector<uint32_t> & indices);
    ~Geometry();

    void set(const char * uniformName, AbstractBuffer * geometryBuffer);
    void setIndices(std::vector<uint32_t> & indices);

    AbstractBuffer * get(const char * name);
    AbstractBuffer * get(const uint32_t index);
    const std::vector<uint32_t> & getIndices();

    bool has(const char * name);
    bool has(const uint32_t index) const;
    bool hasIndices() const;

    inline uint32_t size() const
    {
        return m_attributeBuffers.size();
    }

    inline bool isEmpty() const
    {
        return m_attributeBuffers.size() == 0;
    }


protected:
    std::map<std::string, AbstractBuffer*> m_attributeBuffers;
    std::vector<uint32_t> m_indices;
};

}

#endif /* __GEOMETRY_H__ */
