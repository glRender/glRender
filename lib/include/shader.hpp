#ifndef __SHADER_HPP__		
#define __SHADER_HPP__

#include "base.h"

namespace glRender
{

class Shader
{
private:
    GLuint m_id;         // The unique ID / handle for the shader
    std::string m_typeString; // String representation of the shader type (i.e. "Vertex" or such)
    std::string m_source;     // The shader source code (i.e. the GLSL code itself)

    GLuint m_program;

public:
    Shader(const GLenum &type);
    ~Shader();

    GLuint id();
    const char * source();
    void loadFromString(const char * sourceString);
    bool loadFromFile(const char * filename);
    bool compile();
};

}

#endif /* __SHADER_HPP__ */
