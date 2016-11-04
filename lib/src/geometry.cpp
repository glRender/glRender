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
    for( auto i : m_geometryBuffers)
    {
        delete i.second;
    }
    m_geometryBuffers.clear();
}

void Geometry::set(const char * uniformName, AttributeBuffer* geometryBuffer)
{
    m_geometryBuffers[ uniformName ] = geometryBuffer;
}

void Geometry::setIndices(std::vector<uint> &indices)
{
    m_indices = indices;
}

AttributeBuffer* Geometry::get(const char * name)
{
    std::map<std::string, AttributeBuffer*>::iterator it = m_geometryBuffers.find( name );

    // Found it? Great -return the bound location! Didn't find it? Alert user and halt.
    if ( it != m_geometryBuffers.end() )
    {
        return m_geometryBuffers[ name ];
    }
    else
    {
        std::cout << "Could not find geometry buffer in geometry: " << name << std::endl;
        return nullptr;
    }

}

AttributeBuffer* Geometry::get(const int index)
{
    if (index < m_geometryBuffers.size())
    {
        std::map<std::string, AttributeBuffer*>::iterator it = m_geometryBuffers.begin();
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
    std::map<std::string, AttributeBuffer*>::iterator it = m_geometryBuffers.find( name );

    if ( it != m_geometryBuffers.end() )
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
    if (index < m_geometryBuffers.size())
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
