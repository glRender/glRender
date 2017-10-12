#pragma once

#include "base.h"

#include "vec3.hpp"
#include "vec4.hpp"
#include "mat4.hpp"
#include "shader.hpp"
#include "attribute.h"
#include "geometry.hpp"
#include "textures.hpp"

namespace glRender
{

struct Attribute
{
    uint32_t index;
    int size;
    uint32_t type;
    bool normalized;
    int stride;
    const void * pointer;
};

class ShaderProgram
{
public:
    ShaderProgram();
    ~ShaderProgram();
    uint32_t id();
    void attach(ShaderType type, std::shared_ptr<Shader> shader);
    void detach(ShaderType type);
    void detach();
    bool link();
    void use();
    void disable();
    void fillAttributes(std::shared_ptr<Geometry> geometry);
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

    template<typename T>
    void fillUniformByArray(const char * uniformName, T* value, uint count);

private:
    void setUniformValueByAddress(uint32_t index, float value);
    void setUniformValueByAddress(uint32_t index, int value);
    void setUniformValueByAddress(uint32_t index, int* value, uint count = 1);
    void setUniformValueByAddress(uint32_t index, Vec3 & value);
    void setUniformValueByAddress(uint32_t index, Vec2 * value, uint count = 1);
    void setUniformValueByAddress(uint32_t index, Vec2 & value);
    void setUniformValueByAddress(uint32_t index, Vec4 & value);
    void setUniformValueByAddress(uint32_t index, Mat4 & value);
    void setUniformValueByAddress(uint32_t index, Texture & value);

    struct cmp_str
    {
       bool operator()(char const *a, char const *b)
       {
          return std::strcmp(a, b) < 0;
       }
    };

    std::map<ShaderType, std::shared_ptr<Shader>> m_shaders;

    // Map of attributes and their binding locations
    std::map<const char *, Attribute, cmp_str > attributesList;

    // Map of uniforms and their binding locations
    std::map<const char *, int, cmp_str > uniformsList;

    uint32_t m_lastFreeTextureUnit = 0;
    uint32_t m_programId;   // The unique ID / handle for the shader program
};

using ShaderProgramPtr = std::shared_ptr<ShaderProgram>;

std::shared_ptr<ShaderProgram> createShaderProgramFromFiles(std::map<ShaderType, const char *> pathesToShaders);
std::shared_ptr<ShaderProgram> createShaderProgramFromText(std::map<ShaderType, const char *> textOfShaders);

}
