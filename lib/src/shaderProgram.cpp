#include "shaderProgram.hpp"

#include "resourceManager.hpp"
#include "geometryBuffer.hpp"

namespace glRender {

//ShaderProgram::ShaderProgram() :
//    shaderCount(0)
//{
//    // Generate a unique Id / handle for the shader program
//    // Note: We MUST have a valid rendering context before generating
//    // the programId or it causes a segfault!
//    programId = glCreateProgram();

//}

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
            addUniform( "model" );
            addUniform( "view" );
            addUniform( "projection" );

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
    std::map<std::string, Attribute>::iterator it = attributeLocList.find(attribute);

    // Found it? Great -return the bound location! Didn't find it? Alert user and halt.
    if ( it != attributeLocList.end() )
    {
        return attributeLocList[attribute];
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
//    static GLuint index = -1;
//    index++;

    // printf("%s, type: %d\n", attributeName.c_str(), type );

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

        attributeLocList[ attributeName ] = attr;

        // std::cout << "Attribute " << attributeName << " bound to location: " << attr.index << std::endl;
    }
}

void ShaderProgram::bindBuffers(Geometry *geometry)
{
    geometry->bufferAll();

    // Set up the Vertex attribute pointer for the vVertex attribute
    for( auto attr : attributeLocList )
    {
        GeometryBuffer * buffer = geometry->get( attr.first.c_str() );
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
    std::string textureName = "texture";
    for (GLuint i = 0; i < textures->size(); i++)
    {
        glActiveTexture( GL_TEXTURE0 + i );
        Texture * texture = textures->texture(i);
        if ( texture != nullptr )
        {
            glBindTexture(GL_TEXTURE_2D, texture->getId() );
            setUniform1i( (textureName + patch::to_string(i)).c_str(), i );
        }
    }
}

void ShaderProgram::unbindTextures(Textures * textures)
{
    // Always good practice to set everything back to defaults once configured.
    for (GLuint i = 0; i < textures->size(); ++i)
    {
        glActiveTexture(GL_TEXTURE0 + i);
        glBindTexture(GL_TEXTURE_2D, 0);
    }
}

// Method to returns the bound location of a named uniform
GLuint ShaderProgram::uniform(const char * uniform)
{
    // Note: You could do this method with the single line:
    //
    //      return uniformLocList[uniform];
    //
    // But we're not doing that. Explanation in the attribute() method above.

    // Create an iterator to look through our uniform map and try to find the named uniform
    std::map<std::string, int>::iterator it = uniformLocList.find(uniform);

    // Found it? Great - pass it back! Didn't find it? Alert user and halt.
    if ( it != uniformLocList.end() )
    {
        return uniformLocList[uniform];
    }
    else
    {
        std::cout << "Could not find uniform in shader program: " << uniform << std::endl;
        exit(-1);
    }
}

// Method to add a uniform to the shader and return the bound location
int ShaderProgram::addUniform(const char * uniformName)
{
    uniformLocList[uniformName] = glGetUniformLocation( m_programId, uniformName );

    // Check to ensure that the shader contains a uniform with this name
    if (uniformLocList[uniformName] == -1)
    {
        std::cout << "Could not add uniform: " << uniformName << " - location returned -1!" << std::endl;
    }
    else
    {
        // std::cout << "Uniform " << uniformName << " bound to location: " << uniformLocList[uniformName] << std::endl;
    }

    return uniformLocList[uniformName];
}

void ShaderProgram::addUniformsForTextures(Textures * textures)
{
    // add uniforms for every texture
    for (int i = 0; i < textures->size(); ++i)
    {
        const std::string textureUniformName = textures->textureUniformName( i );
        if ( textureUniformName != "" )
        {
            addUniform( textureUniformName.c_str() );
        }
    }
}

int ShaderProgram::setUniform(const char * uniformName, float value)
{
    addUniform( uniformName );
    setUniform1f( uniformName, value);
}

int ShaderProgram::setUniform(const char * uniformName, int value)
{
    addUniform( uniformName );
    setUniform1i( uniformName, value);
}

int ShaderProgram::setUniform(const char * uniformName, Vec3 & value)
{
    addUniform( uniformName );
    setUniform3f( uniformName, value);
}

int ShaderProgram::setUniform(const char * uniformName, Vec4 & value)
{
    addUniform( uniformName );
    setUniform4f( uniformName, value);
}

int ShaderProgram::setUniform(const char * uniformName, Mat4 & value)
{
    addUniform( uniformName );
    setUniformMatrix4f( uniformName, value);
}

void ShaderProgram::setUniform1f(const char * uniformName, float value)
{
    use();
    glUniform1f( uniform( uniformName ), value );
    disable();
}

void ShaderProgram::setUniform3f(const char * uniformName, Vec3 value)
{
    use();
    glUniform3f( uniform( uniformName ), value.x, value.y, value.z );
    disable();
}

void ShaderProgram::setUniform4f(const char * uniformName, Vec4 value)
{
    use();
    glUniform4f( uniform( uniformName ), value.x, value.y, value.z, value.w );
    disable();
}

void ShaderProgram::setUniformMatrix4f(const char * uniformName, Mat4 value)
{
    use();
    glUniformMatrix4fv( uniform( uniformName ), 1, GL_FALSE, value.get() );
    disable();
}

void ShaderProgram::setUniform1i(const char * uniformName, int value)
{
    use();
    glUniform1i( uniform( uniformName ), value );
    disable();
}

}
