#include "shaderProgram.hpp"

#include "resourceManager.hpp"
#include "geometryBuffer.hpp"
#include "opengl.h"

namespace glRender {

ShaderProgram::ShaderProgram(const char * pathToVertexShader, const char * pathToFragmentShader)
{
    m_programId = glCreateProgram();

    bool vertexShaderReady = false;
    bool fragmentShaderReady = false;
    bool isShadersLinked = false;

    Shader * vertexShader;
    Shader * fragmentShader;

    if (!ResourceManager::getInstance().hasShader(pathToVertexShader))
    {
        vertexShaderReady = ResourceManager::getInstance().initShader(pathToVertexShader, ShaderType::VertexShader);
        if (!vertexShaderReady)
        {
            std::cout << "Can't init vertex shader!" <<std::endl;
        }
    }
    vertexShader = ResourceManager::getInstance().getShader(pathToVertexShader);
    std::cout << " * ShaderVertex " << vertexShader << std::endl;

    if (!ResourceManager::getInstance().hasShader(pathToFragmentShader))
    {
        fragmentShaderReady = ResourceManager::getInstance().initShader(pathToFragmentShader, ShaderType::FragmentShander);
        if (!fragmentShaderReady)
        {
            std::cout << "Can't init fragment shader!" <<std::endl;
        }
    }
    fragmentShader = ResourceManager::getInstance().getShader(pathToFragmentShader);
    std::cout << " * ShaderFragment " << fragmentShader << std::endl;

    attachVertexShader(vertexShader);
    attachFragmentShader(fragmentShader);
    link();
}


// Destructor
ShaderProgram::~ShaderProgram()
{
    detachVertexShader();
    detachFragmentShader();

    // Delete the shader program from the graphics card memory to
    // free all the resources it's been using
    glDeleteProgram(m_programId);
}

uint ShaderProgram::id()
{
    return m_programId;
}

void ShaderProgram::attachVertexShader(Shader *shader)
{
    m_vertexShader = shader;
    glAttachShader( m_programId, shader->id() );
    std::cout << " * Vertex shader attached to programm " << m_programId << std::endl;
}

void ShaderProgram::attachFragmentShader(Shader *shader)
{
    m_fragmentShader = shader;
    glAttachShader( m_programId, shader->id() );
    std::cout << " * Fragment shader attached to programm " << m_programId << std::endl;
}

void ShaderProgram::detachVertexShader()
{
    glDetachShader(m_programId, m_vertexShader->id());
}

void ShaderProgram::detachFragmentShader()
{
    glDetachShader(m_programId, m_fragmentShader->id());
}

// Method to link the shader program and display the link status
bool ShaderProgram::link()
{
    // If we have at least two shaders (like a vertex shader and a fragment shader)...
    if (m_vertexShader != nullptr && m_fragmentShader != nullptr)
    {
        // Perform the linking process
        glLinkProgram(m_programId);

        // Check the status
        GLint linkStatus;
        glGetProgramiv(m_programId, GL_LINK_STATUS, &linkStatus);
        if (linkStatus == GL_FALSE)
        {
            GLint maxLength = 0;
            glGetProgramiv(m_programId, GL_INFO_LOG_LENGTH, &maxLength);

            //The maxLength includes the NULL character
            std::vector<GLchar> infoLog(maxLength);
            glGetProgramInfoLog(m_programId, maxLength, &maxLength, &infoLog[0]);

            //We don't need the program anymore.
            glDeleteProgram(m_programId);

            std::cout << "Shader program linking failed." << std::endl;
        }
        else
        {
            std::cout << "Shader program linking OK." << std::endl;

            detachVertexShader();
            detachFragmentShader();

        }
    }
    else
    {
        std::cout << "Can't link shaders" << std::endl;
    }

}

void ShaderProgram::use()
{
    glUseProgram(m_programId);
}

void ShaderProgram::disable()
{
    glUseProgram(0);
}

void ShaderProgram::fillAttributes(Geometry *geometry)
{
    // Set up the Vertex attribute pointer for the Vertex attribute
    for( auto item : attributesList )
    {
        std::string attributeName = item.first;

        AbstractBuffer * buffer = geometry->get( attributeName.c_str() );
        if (buffer != nullptr)
        {
            buffer->bind();

            glEnableVertexAttribArray( item.second.index );
            glVertexAttribPointer(
                item.second.index,     // Attribute location
                item.second.size,      // Number of elements per vertex, here (x,y,z), so 3
                item.second.type,      // Data type of each element
                item.second.normalized,// Normalised?
                item.second.stride,    // Stride
                item.second.pointer    // Offset
            );
        }

    }

}

void ShaderProgram::bindTextures(Textures * textures)
{
    for (int i=0; i<textures->size(); i++)
    {
        const char * uniformName = textures->textureUniformName(i);
        {
            if (hasUniform<Texture>(uniformName))
            {
                Texture * texture = textures->texture(i);
                if ( texture != nullptr )
                {
                    setUniform<Texture>(uniformName, (*texture));
                }
            }
        }
    }
}

void ShaderProgram::unbindTextures()
{
    while(m_lastFreeTextureUnit >= 1)
    {
        m_lastFreeTextureUnit--;
        glActiveTexture( GL_TEXTURE0 + m_lastFreeTextureUnit );
        glBindTexture(GL_TEXTURE_2D, 0 );
    }
}

void ShaderProgram::setUniformValueByAddress(uint index, float value)
{
    glUniform1f( index, value );
}

void ShaderProgram::setUniformValueByAddress(uint index, int value)
{
    glUniform1i( index, value );
}

void ShaderProgram::setUniformValueByAddress(uint index, uint value)
{
    setUniformValueByAddress(index, static_cast<int>(value));
}

void ShaderProgram::setUniformValueByAddress(uint index, Vec3 & value)
{
    glUniform3f( index, value.x, value.y, value.z );
}

void ShaderProgram::setUniformValueByAddress(uint index, Vec4 & value)
{
    glUniform4f( index, value.x, value.y, value.z, value.w );
}

void ShaderProgram::setUniformValueByAddress(uint index, Mat4 & value)
{
    glUniformMatrix4fv( index, 1, GL_FALSE, value.get() );
}

void ShaderProgram::setUniformValueByAddress(uint index, Texture & value)
{
    glActiveTexture( GL_TEXTURE0 + m_lastFreeTextureUnit );
    glBindTexture(GL_TEXTURE_2D, value.id() );
    glUniform1i(index, m_lastFreeTextureUnit);
    m_lastFreeTextureUnit++;
}

template<typename T >
bool ShaderProgram::hasAttribute(const char * attributeName)
{
    std::map<const char *, Attribute>::iterator it = attributesList.find(attributeName);
    if ( it == attributesList.end() )
    {
        return true;
    }

    return glGetAttribLocation( m_programId, attributeName ) != -1;
}

template<typename T>
int ShaderProgram::attribute(const char * attributeName)
{
    std::map<const char *, Attribute>::iterator it = attributesList.find(attributeName);
    if ( it == attributesList.end() )
    {
        if (addAttribute<T>(attributeName) == false)
        {
            std::cout << "Could not find attribute in shader program: " << attributeName << std::endl;
            return -1;
        }
    }

    return attributesList[attributeName].index;
}

template<typename T>
bool ShaderProgram::addAttribute(const char * attributeName)
{
    int index = glGetAttribLocation( m_programId, attributeName );
    if (index != -1)
    {
        Attribute attr;
        attr.index = index;
        attr.size = sizeof(T) / sizeof(float);
        attr.type = GL_FLOAT;
        attr.normalized = GL_FALSE;
        attr.stride = sizeof(T);
        attr.pointer = (GLvoid*)0;

        attributesList[attributeName] = attr;
    }
    else
    {
        std::cout << "Could not add attribute: " << attributeName << " - location returned -1!" << std::endl;
    }

    return index != -1;
}

template<typename T>
bool ShaderProgram::hasUniform(const char * uniformName)
{
    std::map<const char *, int>::iterator it = uniformsList.find(uniformName);
    if ( it == uniformsList.end() )
    {
        return false;
    }

    return glGetUniformLocation(m_programId, uniformName) != -1;
}

template<typename T>
int ShaderProgram::uniform(const char * uniformName)
{
    std::map<const char *, int>::iterator it = uniformsList.find(uniformName);
    if ( it == uniformsList.end() )
    {
        if (addUniform<T>(uniformName) == false)
        {
            std::cout << "Could not find uniform in shader program: " << uniformName << std::endl;
            return -1;
        }
    }

    return uniformsList[uniformName];
}

template<typename T>
bool ShaderProgram::addUniform(const char * uniformName)
{
    int index = glGetUniformLocation(m_programId, uniformName);
    if (index != -1)
    {
        uniformsList[uniformName] = index;
    }
    else
    {
        std::cout << "Could not add uniform: " << uniformName << " <- location returned -1!" << std::endl;
    }

    return index != -1;
}

template<typename T>
void ShaderProgram::setUniform(const char * uniformName, T & value)
{
    int uniformAddress = uniform<T>(uniformName);
    if (uniformAddress != -1)
    {
        glUseProgram(m_programId);
        setUniformValueByAddress(uniformAddress, value);
    }
    else
    {
        std::cout << "Could not get address of uniform: " + std::string(uniformName) + " <- Location returned -1!" <<std::endl;
    }
}

template bool ShaderProgram::hasAttribute<Vec3>(const char * attributeName);
template bool ShaderProgram::hasAttribute<float>(const char * attributeName);
template bool ShaderProgram::hasAttribute<Vec2>(const char * attributeName);

template int  ShaderProgram::attribute<   Vec3>(const char * attributeName);
template int  ShaderProgram::attribute<   float>(const char * attributeName);
template int  ShaderProgram::attribute<   Vec2>(const char * attributeName);

template bool ShaderProgram::addAttribute<Vec3>(const char * attributeName);
template bool ShaderProgram::addAttribute<float>(const char * attributeName);
template bool ShaderProgram::addAttribute<Vec2>(const char * attributeName);


template bool ShaderProgram::hasUniform<  Vec3>(const char * uniformName);
template bool ShaderProgram::hasUniform<  float>(const char * uniformName);
template bool ShaderProgram::hasUniform<  Mat4>(const char * uniformName);

template int  ShaderProgram::uniform<     Vec3>(const char * uniformName);
template int  ShaderProgram::uniform<     float>(const char * uniformName);
template int  ShaderProgram::uniform<     Mat4>(const char * uniformName);

template bool ShaderProgram::addUniform<  Vec3>(const char * uniformName);
template bool ShaderProgram::addUniform<  float>(const char * uniformName);
template bool ShaderProgram::addUniform<  Mat4>(const char * uniformName);

template void ShaderProgram::setUniform<  Vec3>(const char * uniformName, Vec3 & value);
template void ShaderProgram::setUniform<  float>(const char * uniformName, float & value);
template void ShaderProgram::setUniform<  Mat4>(const char * uniformName, Mat4 & value);

}
