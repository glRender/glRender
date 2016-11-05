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

void Geometry::set(const char * uniformName, AttributeBuffer* geometryBuffer)
{
    m_attributeBuffers[ uniformName ] = geometryBuffer;
}

void Geometry::setIndices(std::vector<uint> &indices)
{
    m_indices = indices;
}

AttributeBuffer* Geometry::get(const char * name)
{
    std::map<std::string, AttributeBuffer*>::iterator it = m_attributeBuffers.find( name );

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

AttributeBuffer* Geometry::get(const int index)
{
    if (index < m_attributeBuffers.size())
    {
        std::map<std::string, AttributeBuffer*>::iterator it = m_attributeBuffers.begin();
        for(int i=0; i<index; i++)
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
    std::map<std::string, AttributeBuffer*>::iterator it = m_attributeBuffers.find( name );

    if ( it != m_attributeBuffers.end() )
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool Geometry::has(const int index) const
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
