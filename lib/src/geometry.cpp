#include "geometry.hpp"

namespace glRender {
Geometry::Geometry(std::vector<uint> & indices)
    : m_indices(indices)
{

}

Geometry::Geometry()
{

}

Geometry::~Geometry()
{
    for( auto i : m_attributeBuffers)
    {
        delete i.second;
    }
    m_attributeBuffers.clear();
}

void Geometry::set(const char * uniformName, AbstractBuffer* geometryBuffer)
{
    m_attributeBuffers[ uniformName ] = geometryBuffer;
}

void Geometry::setIndices(std::vector<uint> &indices)
{
    m_indices = indices;
}

AbstractBuffer* Geometry::get(const char * name)
{
    std::map<std::string, AbstractBuffer*>::iterator it = m_attributeBuffers.find( name );

    // Found it? Great -return the bound location! Didn't find it? Alert user and halt.
    if ( it != m_attributeBuffers.end() )
    {
        return m_attributeBuffers[ name ];
    }
    else
    {
        std::cout << "Could not find geometry buffer in geometry: " << name << std::endl;
        return nullptr;
    }

}

AbstractBuffer* Geometry::get(const uint index)
{
    if (index < m_attributeBuffers.size())
    {
        std::map<std::string, AbstractBuffer*>::iterator it = m_attributeBuffers.begin();
        for(uint i=0; i<index; i++)
        {
            ++it;
        }

        return it->second;

    } else {
        std::cout << "Geometry buffer with index: " << index << " does not exist!" << std::endl;
        return nullptr;

    }

}

const std::vector<uint> & Geometry::getIndices()
{
    return m_indices;
}

bool Geometry::has(const char * name)
{
    std::map<std::string, AbstractBuffer*>::iterator it = m_attributeBuffers.find( name );

    if ( it != m_attributeBuffers.end() )
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool Geometry::has(const uint index) const
{
    if (index < m_attributeBuffers.size())
    {
        return true;

    } else {
        return false;
    }
}

bool Geometry::hasIndices() const
{
    return m_indices.size() > 0;
}
    
}
