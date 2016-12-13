#ifndef __SHADER_PROGRAM_HPP__		
#define __SHADER_PROGRAM_HPP__

#include "base.h"

#include "vec3.hpp"
#include "vec4.hpp"
#include "mat4.hpp"
#include "shader.hpp"
#include "attribute.h"
#include "geometry.hpp"
#include "textures.hpp"
//#include "opengl.h"

namespace glRender
{

struct Attribute
{
    uint index;
    int size;
    uint type;
    bool normalized;
    int stride;
    const void * pointer;
};

class ShaderProgram
{
public:
    ShaderProgram(const char * pathToVertexShader, const char * pathToFragmentShader);
    ~ShaderProgram();
    uint id();
    void attachVertexShader(Shader * shader);
    void attachFragmentShader(Shader * shader);
    void detachVertexShader();
    void detachFragmentShader();
    bool link();
    void use();
    void disable();
    void fillAttributes(Geometry * geometry);
    void bindTextures(Textures * textures);
    void unbindTextures();

    template<typename T>
    bool hasAttribute(const char * attributeName);

    template<typename T>
    int attribute(const char * attributeName);

    template<typename T>
    bool addAttribute(const char * attributeName);

    template<typename T>
    bool hasUniform(const char * uniformName);

    template<typename T>
    int uniform(const char * uniformName);

    template<typename T>
    bool addUniform(const char * uniformName);

    template<typename T>
    void setUniform(const char * uniformName, T & value);

private:
    void setUniformValueByAddress(uint index, float value);
    void setUniformValueByAddress(uint index, int value);
    void setUniformValueByAddress(uint index, uint value);
    void setUniformValueByAddress(uint index, Vec3 & value);
    void setUniformValueByAddress(uint index, Vec4 & value);
    void setUniformValueByAddress(uint index, Mat4 & value);
    void setUniformValueByAddress(uint index, Texture & value);

    friend class Model;

    Shader * m_vertexShader = nullptr;
    Shader * m_fragmentShader = nullptr;

    struct cmp_str
    {
       bool operator()(char const *a, char const *b)
       {
          return std::strcmp(a, b) < 0;
       }
    };

    // Map of attributes and their binding locations
    std::map<const char *, Attribute, cmp_str > attributesList;

    // Map of uniforms and their binding locations
    std::map<const char *, int, cmp_str > uniformsList;

    uint m_lastFreeTextureUnit = 0;
    uint m_programId;   // The unique ID / handle for the shader program

};

}

#endif /* __SHADER_PROGRAM_HPP__ */
