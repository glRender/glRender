#ifndef __SHADER_PROGRAM_HPP__		
#define __SHADER_PROGRAM_HPP__

#include "base.h"

#include "shader.hpp"
#include "attribute.h"

namespace glRender
{
    
enum AttributeType
{
    XYZW,
    XYZ,
    XY,
    X,
    UVW,
    UV,
    RGB,
    RGBA
};

class ShaderProgram
{

public:
    GLuint programId;   // The unique ID / handle for the shader program

    ShaderProgram();
    ShaderProgram(const std::string pathToVertexShader, const std::string pathToFragmentShader);
    ~ShaderProgram();

    void add(Shader shader);
    void link();
    void disable();
    void use();

    Attribute attribute(const std::string &attribute);
    GLuint uniform(const std::string &uniform);

    // int addAttribute(const std::string &attributeName, GLint size = 3, GLenum type = GL_FLOAT, GLboolean normalized = GL_FALSE, GLsizei stride = 0, const GLvoid * pointer = (GLvoid*)0);
    int setAttribute(const std::string &attributeName, AttributeType type);

    int addUniform(const std::string &uniformName);
    int setUniform(const std::string &uniformName, float value);
    int setUniform(const std::string &uniformName, int value);
    int setUniform(const std::string &uniformName, Vec3 & value);
    int setUniform(const std::string &uniformName, Vec4 & value);
    int setUniform(const std::string &uniformName, Mat4 & value);

    void setUniform1f(const std::string &uniformName, float value);
    void setUniform3f(const std::string &uniformName, Vec3 value);
    void setUniform4f(const std::string &uniformName, Vec4 value);
    void setUniformMatrix4fv(const std::string &uniformName, Mat4 value);
    void setUniform1i(const std::string &uniformName, int value);

private:
    friend class Model;

    GLuint shaderCount; // How many shaders are attached to the shader program

    // Map of attributes and their binding locations
    std::map<std::string, Attribute> attributeLocList;

    // Map of uniforms and their binding locations
    std::map<std::string,int> uniformLocList;
};

}

#endif /* __SHADER_PROGRAM_HPP__ */
