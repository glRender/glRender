#ifndef __GEOMETRY_BUFFER__
#define __GEOMETRY_BUFFER__

#include <stdlib.h>
#include <string>

#include <vector>

#include "vec3.hpp"
#include "vec4.hpp"
#include "mat4.hpp"

#include "opengl.h"
#include "stdlib.h"
#include "stdio.h"

namespace glRender
{

class GeometryBuffer
{
protected:
    GLuint m_id;

public:
    virtual const int size() = 0;
    virtual const int memorySize() = 0;
    virtual void bufferData() = 0;

    const GLuint id()
    {
        return m_id;
    }

    void bind()
    {
        // printf("GeometryBuffer: bind(), id: %d\n", id() );
        glBindBuffer ( GL_ARRAY_BUFFER, id() );

    }

    void unbind()
    {
        // printf("GeometryBuffer: unbind(), id: %d\n", id() );
        glBindBuffer ( GL_ARRAY_BUFFER, 0 );

    }

};

class GeometryBufferFloat : public GeometryBuffer
{
protected:
    std::vector<GLfloat> m_data;

public:
    GeometryBufferFloat(std::vector<GLfloat> data) :
        m_data(data)
    {       

    };

    virtual void bufferData()
    {
        glGenBuffers(1, &m_id);
        glBindBuffer(GL_ARRAY_BUFFER, m_id);
        glBufferData(GL_ARRAY_BUFFER, m_data.size() * sizeof(GLfloat), m_data.data(), GL_STATIC_DRAW);

    }

    virtual const int size()
    {
        return m_data.size();
    }

    virtual const int memorySize()
    {
        return m_data.size() * sizeof(GLfloat);
    }

    ~GeometryBufferFloat()
    {
        glDeleteBuffers(1, &m_id);

    };

};

class GeometryBufferVec3 : public GeometryBuffer
{
protected:
    std::vector<Vec3> m_data;

public:
    GeometryBufferVec3(std::vector<Vec3> data) :
        m_data(data)
    {       

    };

    virtual void bufferData()
    {
        glGenBuffers(1, &m_id);
        glBindBuffer(GL_ARRAY_BUFFER, m_id);
        glBufferData(GL_ARRAY_BUFFER, m_data.size() * sizeof(Vec3), m_data.data(), GL_STATIC_DRAW);

    }

    virtual const int size()
    {
        return m_data.size();
    }

    virtual const int memorySize()
    {
        return m_data.size() * sizeof(Vec3);
    }

    ~GeometryBufferVec3()
    {
        glDeleteBuffers(1, &m_id);

    };

};

class GeometryBufferVec2 : public GeometryBuffer
{

public:
    GeometryBufferVec2(std::vector<Vec2> data) :
        m_data(data)
    {       

    };

    virtual void bufferData()
    {
        glGenBuffers(1, &m_id);
        glBindBuffer(GL_ARRAY_BUFFER, m_id);
        glBufferData(GL_ARRAY_BUFFER, m_data.size() * sizeof(Vec2), m_data.data(), GL_STATIC_DRAW);

    }

    virtual const int size()
    {
        return m_data.size();
    }

    virtual const int memorySize()
    {
        return m_data.size() * sizeof(Vec2);
    }

    ~GeometryBufferVec2()
    {
        glDeleteBuffers(1, &m_id);

    };

protected:
    std::vector<Vec2> m_data;

};

class GeometryBufferUint : public GeometryBuffer
{
protected:
    std::vector<GLuint> m_data;

public:
    GeometryBufferUint(std::vector<GLuint> data) :
        m_data(data)
    {

    };

    virtual void bufferData()
    {
        glGenBuffers(1, &m_id);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_id);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_data.size() * sizeof(GLuint), m_data.data(), GL_STATIC_DRAW);

    }

    virtual const int size()
    {
        return m_data.size();
    }

    virtual const int memorySize()
    {
        return m_data.size() * sizeof(GLuint);
    }

    ~GeometryBufferUint()
    {
        glDeleteBuffers(1, &m_id);

    };

};

}

#endif /* __GEOMETRY_BUFFER__ */
