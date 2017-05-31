#pragma once

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
    Shader(const char * text, ShaderType type);
    ~Shader();

    uint32_t id();
    const char * source();
//    void loadFromString(const char * sourceString);
//    bool loadFromFile(const char * filename);
    bool compile();

private:
    uint32_t m_id;         // The unique ID / handle for the shader
    std::string m_typeString; // String representation of the shader type (i.e. "Vertex" or such)
    ShaderType m_type;
    std::string m_source;     // The shader source code (i.e. the GLSL code itself)

    uint32_t m_program;
};

}
