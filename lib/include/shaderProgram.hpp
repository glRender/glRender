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
    GLuint m_programId;   // The unique ID / handle for the shader program

    ShaderProgram(const char * pathToVertexShader, const char * pathToFragmentShader);
    ~ShaderProgram();

    inline GLuint id()
    {
        return m_programId;
    }

    void attachVertexShader(Shader * shader);
    void attachFragmentShader(Shader * shader);

    void detachVertexShader();
    void detachFragmentShader();

    bool link();

    inline void use()
    {
        glUseProgram(m_programId);
    }

    inline void disable()
    {
        glUseProgram(0);
    }

    Attribute attribute(const char * attribute);
    bool hasAttribute(const char * attribute);
    void setAttributeType(const char * attributeName, AttributeType type);
    void bindAttributesWithBuffers(Geometry * geometry);
    void bindTextures(Textures * textures);
    void unbindTextures(Textures * textures);

    template<typename T>
    int uniform(const char * uniformName)
    {
        std::string typeName = typeid(T).name();
        std::map<std::string, int>::iterator it = uniformsList.find( typeName+"+"+std::string(uniformName) );
        if ( it == uniformsList.end() )
        {
            if (!addUniform<T>(uniformName))
            {
                std::cout << "Could not find uniform in shader program: " << uniformName << std::endl;
                return -1;
            }
        }

        return uniformsList[typeName+"+"+std::string(uniformName)];
    }

    template<typename T>
    bool addUniform(const char * uniformName)
    {
        int index = glGetUniformLocation( m_programId, uniformName );
        if (index != -1)
        {
            std::string typeName = typeid(T).name();
            uniformsList[typeName+"+"+std::string(uniformName)] = index;
        }
        else
        {
            std::cout << "Could not add uniform: " << uniformName << " - location returned -1!" << std::endl;
        }

        return index != -1;
    }

    template<typename T>
    void setUniform(const char * uniformName, T & value)
    {
        glUseProgram(m_programId);
        setUniformValueByAddress(uniform<T>( uniformName ), value);
    }


private:
    void setUniformValueByAddress(GLuint index, float value);
    void setUniformValueByAddress(GLuint index, int value);
    void setUniformValueByAddress(GLuint index, uint value);
    void setUniformValueByAddress(GLuint index, Vec3 & value);
    void setUniformValueByAddress(GLuint index, Vec4 & value);
    void setUniformValueByAddress(GLuint index, Mat4 & value);

    friend class Model;

    Shader * m_vertexShader = nullptr;
    Shader * m_fragmentShader = nullptr;

    // Map of attributes and their binding locations
    std::map<std::string, Attribute> attributesList;

    // Map of uniforms and their binding locations
    std::map<std::string,int> uniformsList;
};

}

#endif /* __SHADER_PROGRAM_HPP__ */
