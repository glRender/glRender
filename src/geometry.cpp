#include "geometry.hpp"

namespace glRender {
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

void Geometry::setGeometryBuffer(const std::string& uniformName, GeometryBuffer* geometryBuffer)
{
    m_geometryBuffers[ uniformName ] = geometryBuffer;
}

GeometryBuffer* Geometry::get(const std::string& name)
{
    std::map<std::string, GeometryBuffer*>::iterator it = m_geometryBuffers.find( name );

    // Found it? Great -return the bound location! Didn't find it? Alert user and halt.
    if ( it != m_geometryBuffers.end() )
    {
        return m_geometryBuffers[ name ];
    }
    else
    {
        std::cout << "Could not find geometry buffer in geometry: " << name << std::endl;
        exit(-1);
    }

}

GeometryBuffer* Geometry::get(const int index)
{
    if (index < m_geometryBuffers.size())
    {
        std::map<std::string, GeometryBuffer*>::iterator it = m_geometryBuffers.begin();
        for(int i=0; i<index; i++)
        {
            ++it;
        }

        return it->second;

    } else {
        std::cout << "Geometry buffer with index: " << index << " does not exist!" << std::endl;
        exit(-1);

    }

}

bool Geometry::isExist(const std::string& name)
{
    std::map<std::string, GeometryBuffer*>::iterator it = m_geometryBuffers.find( name );

    if ( it != m_geometryBuffers.end() )
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool Geometry::isExist(const int index)
{
    if (index < m_geometryBuffers.size())
    {
        return true;

    } else {
        return false;
    }
}

unsigned int Geometry::size()
{
    return m_geometryBuffers.size();
}
    
}
