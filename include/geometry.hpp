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
	void setGeometryBuffer(const char * uniformName, GeometryBuffer * geometryBuffer);

    GeometryBuffer * get(const char * name);
    GeometryBuffer * get(const int index);

    bool isExist(const char * name);
    bool isExist(const int index);

    unsigned int size();

	Geometry();
	~Geometry();

protected:
	friend class Mesh;
	std::map<std::string, GeometryBuffer*> m_geometryBuffers;

};

}

#endif /* __GEOMETRY_H__ */
