#ifndef __SHADER_HPP__		
#define __SHADER_HPP__

#include "base.h"

namespace glRender
{

enum class ShaderType
{
//    NoType,
    VertexShader,
    FragmentShander
};

class Shader
{
public:
    Shader(ShaderType type);
    ~Shader();

    uint id();
    const char * source();
    void loadFromString(const char * sourceString);
    bool loadFromFile(const char * filename);
    bool compile();

private:
    uint m_id;         // The unique ID / handle for the shader
    std::string m_typeString; // String representation of the shader type (i.e. "Vertex" or such)
    ShaderType m_type;
    std::string m_source;     // The shader source code (i.e. the GLSL code itself)

    uint m_program;
};

}

#endif /* __SHADER_HPP__ */
