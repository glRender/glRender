#include "shaderProgram.hpp"

#include "resourceManager.hpp"
#include "geometryBuffer.hpp"

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
        vertexShaderReady = ResourceManager::getInstance().initShader(pathToVertexShader, GL_VERTEX_SHADER);
        if (!vertexShaderReady)
        {
            std::cout << "Can't init vertex shader!" <<std::endl;
        }
    }
    vertexShader = ResourceManager::getInstance().getShader(pathToVertexShader);
    std::cout << " * ShaderVertex " << vertexShader << std::endl;

    if (!ResourceManager::getInstance().hasShader(pathToFragmentShader))
    {
        fragmentShaderReady = ResourceManager::getInstance().initShader(pathToFragmentShader, GL_FRAGMENT_SHADER);
        if (!fragmentShaderReady)
        {
            std::cout << "Can't init fragment shader!" <<std::endl;
        }
    }
    fragmentShader = ResourceManager::getInstance().getShader(pathToFragmentShader);
    std::cout << " * ShaderFragment " << fragmentShader << std::endl;

//    Shader * vertexShader = new Shader( GL_VERTEX_SHADER );
//    vertexShader->loadFromFile( pathToVertexShader );
//    vertexShader->compile();

//    Shader * fragmentShader = new Shader( GL_FRAGMENT_SHADER );
//    fragmentShader->loadFromFile( pathToFragmentShader );
//    fragmentShader->compile();
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

void ShaderProgram::fillAttributes(Geometry *geometry)
{
    // Set up the Vertex attribute pointer for the Vertex attribute
    for( auto item : attributesList )
    {
        std::string key = item.first;
        std::vector<std::string> words = split(key, '+');
        std::string typeName = words[0];
        std::string attributeName = words[1];

        AttributeBuffer * buffer = geometry->get( attributeName.c_str() );
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
    std::string textureTypeName = typeid(Texture).name();

    uint textureIndex = 0;

    for ( auto item : uniformsList )
    {
        std::string key = item.first;
        std::vector<std::string> words = split(key, '+');
        std::string typeName = words[0];
        std::string uniformName = words[1];

        if (typeName == textureTypeName)
        {
            glActiveTexture( GL_TEXTURE0 + textureIndex );
            if (textures->isExistTexture(textureIndex))
            {
                Texture * texture = textures->texture(textureIndex);
                if ( texture != nullptr )
                {
                    glBindTexture(GL_TEXTURE_2D, texture->id() );
                }
                textureIndex++;
            }
        }
    }
}

void ShaderProgram::unbindTextures(Textures * textures)
{
    std::string textureTypeName = typeid(Texture).name();

    uint textureIndex = 0;

    for ( auto item : uniformsList )
    {
        std::string key = item.first;
        std::vector<std::string> words = split(key, '+');
        std::string typeName = words[0];
        std::string uniformName = words[1];

        if (typeName == textureTypeName)
        {
            glActiveTexture( GL_TEXTURE0 + textureIndex );
            if (textures->isExistTexture(textureIndex))
            {
                glBindTexture(GL_TEXTURE_2D, 0);
                textureIndex++;
            }
        }
    }
}

void ShaderProgram::setUniformValueByAddress(GLuint index, float value)
{
    glUniform1f( index, value );
}

void ShaderProgram::setUniformValueByAddress(GLuint index, int value)
{
    glUniform1i( index, value );
}

void ShaderProgram::setUniformValueByAddress(GLuint index, uint value)
{
    setUniformValueByAddress(index, static_cast<int>(value));
}

void ShaderProgram::setUniformValueByAddress(GLuint index, Vec3 & value)
{
    glUniform3f( index, value.x, value.y, value.z );
}

void ShaderProgram::setUniformValueByAddress(GLuint index, Vec4 & value)
{
    glUniform4f( index, value.x, value.y, value.z, value.w );
}

void ShaderProgram::setUniformValueByAddress(GLuint index, Mat4 & value)
{
    glUniformMatrix4fv( index, 1, GL_FALSE, value.get() );
}

}
