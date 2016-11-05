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

// Returns the bound location of a named attribute
Attribute ShaderProgram::attribute(const char * attribute)
{
    // You could do this function with the single line:
    //
    //      return attributeLocList[attribute];
    //
    // BUT, if you did, and you asked it for a named attribute
    // which didn't exist, like, attributeLocList["ThisAttribDoesn'tExist!"]
    // then the method would return an invalid value which will likely cause
    // the program to segfault. So we're making sure the attribute asked
    // for exists, and if it doesn't we can alert the user and stop rather than bombing out later.

    // Create an iterator to look through our attribute map and try to find the named attribute
    std::map<std::string, Attribute>::iterator it = attributesList.find(attribute);

    // Found it? Great -return the bound location! Didn't find it? Alert user and halt.
    if ( it != attributesList.end() )
    {
        return attributesList[attribute];
    }
    else
    {
        std::cout << "Could not find attribute in shader program: " << attribute << std::endl;
        return {0, 0, 0, 0, 0};
//        exit(-1);
    }
}

bool ShaderProgram::hasAttribute(const char * attributeName)
{
    GLuint index = glGetAttribLocation( m_programId, attributeName );
    return index != -1;
}

// Method to add an attrbute to the shader and return the bound location
void ShaderProgram::setAttributeType(const char * attributeName, AttributeType type)
{
    GLuint index = glGetAttribLocation( m_programId, attributeName );
    // Check to ensure that the shader contains an attribute with this name
    if (index == -1)
    {
        std::cout << "Could not add attribute: " << attributeName << " - location returned -1!" << std::endl;
        exit(-1);
    }
    else
    {
        Attribute attr;

        switch( type )
        {
            case AttributeType::XYZW: {
                attr.index = index;
                attr.size = 4;
                attr.type = GL_FLOAT;
                attr.normalized = GL_FALSE;
                attr.stride = 4 * sizeof(GLfloat);
                attr.pointer = (GLvoid*)0;
            }; break;

            case AttributeType::XYZ: {
                attr.index = index;
                attr.size = 3;
                attr.type = GL_FLOAT;
                attr.normalized = GL_FALSE;
                attr.stride = 3 * sizeof(GLfloat);
                attr.pointer = (GLvoid*)0;
            }; break;

            case AttributeType::XY: {
                attr.index = index;
                attr.size = 2;
                attr.type = GL_FLOAT;
                attr.normalized = GL_FALSE;
                attr.stride = 2 * sizeof(GLfloat);
                attr.pointer = (GLvoid*)0;
            }; break;

            case AttributeType::X: {
                attr.index = index;
                attr.size = 1;
                attr.type = GL_FLOAT;
                attr.normalized = GL_FALSE;
                attr.stride = 1 * sizeof(GLfloat);
                attr.pointer = (GLvoid*)0;
            }; break;

            case AttributeType::UVW: {
                attr.index = index;
                attr.size = 3;
                attr.type = GL_FLOAT;
                attr.normalized = GL_FALSE;
                attr.stride = 3 * sizeof(GLfloat);
                attr.pointer = (GLvoid*)0;

            }; break;

            case AttributeType::UV: {
                attr.index = index;
                attr.size = 2;
                attr.type = GL_FLOAT;
                attr.normalized = GL_FALSE;
                attr.stride = 2 * sizeof(GLfloat);
                attr.pointer = (GLvoid*)0;

            }; break;

            case AttributeType::RGB: {
                attr.index = index;
                attr.size = 3;
                attr.type = GL_FLOAT;
                attr.normalized = GL_FALSE;
                attr.stride = 3 * sizeof(GLfloat);
                attr.pointer = (GLvoid*)0;

            }; break;

            case AttributeType::RGBA: {
                attr.index = index;
                attr.size = 4;
                attr.type = GL_FLOAT;
                attr.normalized = GL_FALSE;
                attr.stride = 4 * sizeof(GLfloat);
                attr.pointer = (GLvoid*)0;

            }; break;
        }

        attributesList[ attributeName ] = attr;
    }
}

void ShaderProgram::bindAttributesWithBuffers(Geometry *geometry)
{
    // Set up the Vertex attribute pointer for the Vertex attribute
    for( auto attr : attributesList )
    {
        AttributeBuffer * buffer = geometry->get( attr.first.c_str() );
        if (buffer != nullptr)
        {
            buffer->bind();

            glEnableVertexAttribArray( attr.second.index );
            glVertexAttribPointer(
                attr.second.index,     // Attribute location
                attr.second.size,      // Number of elements per vertex, here (x,y,z), so 3
                attr.second.type,      // Data type of each element
                attr.second.normalized,// Normalised?
                attr.second.stride,    // Stride
                attr.second.pointer    // Offset
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
                    setUniform<uint>( uniformName.c_str(), textureIndex );
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
