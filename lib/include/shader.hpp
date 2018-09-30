#pragma once

#include "base.h"

namespace glRender
{

enum class ShaderType
{
//    NoType,
    VertexShader,
    FragmentShader
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
    std::string m_source;     // The shader source code (i.e. the GLSL code itself)
};

std::shared_ptr<Shader> createShaderFromFile(const char * pathToFile, ShaderType type);
std::shared_ptr<Shader> createShaderFromText(const char * textOfShader, ShaderType type);

}
