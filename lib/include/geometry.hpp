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
    Geometry(std::vector<uint> & indices);
    ~Geometry();

    void set(const char * uniformName, AttributeBuffer * geometryBuffer);
    void setIndices(std::vector<uint> & indices);

    AttributeBuffer * get(const char * name);
    AttributeBuffer * get(const int index);
    const std::vector<uint> & getIndices();

    bool has(const char * name);
    bool has(const int index) const;
    bool hasIndices() const;

    inline uint size() const
    {
        return m_attributeBuffers.size();
    }

    inline bool isEmpty() const
    {
        return m_attributeBuffers.size() == 0;
    }


protected:
    std::map<std::string, AttributeBuffer*> m_attributeBuffers;
    std::vector<uint> m_indices;
};

}

#endif /* __GEOMETRY_H__ */
