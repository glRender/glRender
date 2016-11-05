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

    void fillAttributes(Geometry * geometry);
    void bindTextures(Textures * textures);
    void unbindTextures(Textures * textures);

    template<typename T>
    bool hasAttribute(const char * attributeName)
    {
        std::string typeName = typeid(T).name();
        for( auto item : attributesList )
        {
            std::string key = item.first;
            std::vector<std::string> words = split(key, '+');
            std::string itemTypeName = words[0];
            std::string attributeName = words[1];

            if (itemTypeName == typeName && attributeName == std::string(attributeName))
            {
                return true;
            }
        }

        GLuint index = glGetAttribLocation( m_programId, attributeName );
        return index != -1;
    }

    template<typename T>
    int attribute(const char * attributeName)
    {
        std::string typeName = typeid(T).name();
        std::map<std::string, int>::iterator it = uniformsList.find( typeName+"+"+std::string(attributeName) );
        if ( it == uniformsList.end() )
        {
            if (!addAttribute<T>(attributeName))
            {
                std::cout << "Could not find attribute in shader program: " << attributeName << std::endl;
                return -1;
            }
        }

        return uniformsList[typeName+"+"+std::string(attributeName)];
    }

    template<typename T>
    bool addAttribute(const char * attributeName)
    {
        int index = glGetAttribLocation( m_programId, attributeName );
        if (index != -1)
        {
            std::string typeName = typeid(T).name();
            Attribute attr;
            attr.index = index;
            attr.size = sizeof(T) / sizeof(float);
            attr.type = GL_FLOAT;
            attr.normalized = GL_FALSE;
            attr.stride = sizeof(T);
            attr.pointer = (GLvoid*)0;

            attributesList[typeName+"+"+std::string(attributeName)] = attr;
        }
        else
        {
            std::cout << "Could not add attribute: " << attributeName << " - location returned -1!" << std::endl;
        }

        return index != -1;
    }

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
