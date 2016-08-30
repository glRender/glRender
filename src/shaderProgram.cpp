#include "shaderProgram.hpp"

namespace glRender {

ShaderProgram::ShaderProgram() :
    shaderCount(0)
{
    // Generate a unique Id / handle for the shader program
    // Note: We MUST have a valid rendering context before generating
    // the programId or it causes a segfault!
    programId = glCreateProgram();

}

ShaderProgram::ShaderProgram(const std::string pathToVertexShader, const std::string pathToFragmentShader) :
    ShaderProgram::ShaderProgram()
{
    Shader * shaderVertex = new Shader( GL_VERTEX_SHADER );
    shaderVertex->loadFromFile( pathToVertexShader );
    shaderVertex->compile();

    Shader * shaderFragment = new Shader( GL_FRAGMENT_SHADER );
    shaderFragment->loadFromFile( pathToFragmentShader );
    shaderFragment->compile();

    add( *shaderVertex );
    add( *shaderFragment );
    link();

}


// Destructor
ShaderProgram::~ShaderProgram()
{
    // Delete the shader program from the graphics card memory to
    // free all the resources it's been using
    glDeleteProgram(programId);
}


// Method to attach a shader to the shader program
void ShaderProgram::add(Shader shader)
{
    // Attach the shader to the program
    // Note: We identify the shader by its unique Id value
    glAttachShader( programId, shader.id() );

    // Increment the number of shaders we have associated with the program
    shaderCount++;
}


// Method to link the shader program and display the link status
void ShaderProgram::link()
{
    // If we have at least two shaders (like a vertex shader and a fragment shader)...
    if (shaderCount >= 2)
    {
        // Perform the linking process
        glLinkProgram(programId);

        // Check the status
        GLint linkStatus;
        glGetProgramiv(programId, GL_LINK_STATUS, &linkStatus);
        if (linkStatus == GL_FALSE)
        {
            std::cout << "Shader program linking failed." << std::endl;
            // glfwTerminate();
        }
        else
        {
            addUniform( "model" );
            addUniform( "view" );
            addUniform( "projection" );

            std::cout << "Shader program linking OK." << std::endl;
        }
    }
    else
    {
        std::cout << "Can't link shaders - you need at least 2, but attached shader count is only: " << shaderCount << std::endl;
        // glfwTerminate();
    }

}

// Method to enable the shader program
void ShaderProgram::use()
{
    glUseProgram(programId);

}


// Method to disable the shader program
void ShaderProgram::disable()
{
    glUseProgram(0);
}

// Returns the bound location of a named attribute
Attribute ShaderProgram::attribute(const std::string &attribute)
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
        exit(-1);
    }
}


// Method to returns the bound location of a named uniform
GLuint ShaderProgram::uniform(const std::string &uniform)
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


// Method to add an attrbute to the shader and return the bound location
int ShaderProgram::setAttribute(const std::string &attributeName, AttributeType type)
{
    static GLuint m_lastIndex = -1;
    m_lastIndex++;

    // printf("%s, type: %d\n", attributeName.c_str(), type );

    // GLuint index = glGetAttribLocation( programId, attributeName.c_str() );
    // Check to ensure that the shader contains an attribute with this name
    if (m_lastIndex == -1)
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
                attr.index = m_lastIndex;
                attr.size = 4;
                attr.type = GL_FLOAT;
                attr.normalized = GL_FALSE;
                attr.stride = 4 * sizeof(GLfloat);
                attr.pointer = (GLvoid*)0;
            }; break;

            case AttributeType::XYZ: {
                attr.index = m_lastIndex;
                attr.size = 3;
                attr.type = GL_FLOAT;
                attr.normalized = GL_FALSE;
                attr.stride = 3 * sizeof(GLfloat);
                attr.pointer = (GLvoid*)0;
            }; break;

            case AttributeType::XY: {
                attr.index = m_lastIndex;
                attr.size = 2;
                attr.type = GL_FLOAT;
                attr.normalized = GL_FALSE;
                attr.stride = 2 * sizeof(GLfloat);
                attr.pointer = (GLvoid*)0;
            }; break;

            case AttributeType::X: {
                attr.index = m_lastIndex;
                attr.size = 1;
                attr.type = GL_FLOAT;
                attr.normalized = GL_FALSE;
                attr.stride = 1 * sizeof(GLfloat);
                attr.pointer = (GLvoid*)0;
            }; break;

            case AttributeType::UVW: {
                attr.index = m_lastIndex;
                attr.size = 3;
                attr.type = GL_FLOAT;
                attr.normalized = GL_FALSE;
                attr.stride = 3 * sizeof(GLfloat);
                attr.pointer = (GLvoid*)0;

            }; break;

            case AttributeType::UV: {
                attr.index = m_lastIndex;
                attr.size = 2;
                attr.type = GL_FLOAT;
                attr.normalized = GL_FALSE;
                attr.stride = 2 * sizeof(GLfloat);
                attr.pointer = (GLvoid*)0;

            }; break;

            case AttributeType::RGB: {
                attr.index = m_lastIndex;
                attr.size = 3;
                attr.type = GL_FLOAT;
                attr.normalized = GL_FALSE;
                attr.stride = 3 * sizeof(GLfloat);
                attr.pointer = (GLvoid*)0;

            }; break;

            case AttributeType::RGBA: {
                attr.index = m_lastIndex;
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

    return m_lastIndex;
}


// Method to add a uniform to the shader and return the bound location
int ShaderProgram::addUniform(const std::string &uniformName)
{
    uniformLocList[uniformName] = glGetUniformLocation( programId, uniformName.c_str() );

    // Check to ensure that the shader contains a uniform with this name
    if (uniformLocList[uniformName] == -1)
    {
        std::cout << "Could not add uniform: " << uniformName << " - location returned -1!" << std::endl;
        exit(-1);
    }
    else
    {
        // std::cout << "Uniform " << uniformName << " bound to location: " << uniformLocList[uniformName] << std::endl;
    }

    return uniformLocList[uniformName];
}

int ShaderProgram::setUniform(const std::string &uniformName, float value)
{
    addUniform( uniformName );
    setUniform1f( uniformName, value);
}

int ShaderProgram::setUniform(const std::string &uniformName, int value)
{
    addUniform( uniformName );
    setUniform1i( uniformName, value);
}

int ShaderProgram::setUniform(const std::string &uniformName, Vec3 & value)
{
    addUniform( uniformName );
    setUniform3f( uniformName, value);
}

int ShaderProgram::setUniform(const std::string &uniformName, Vec4 & value)
{
    addUniform( uniformName );
    setUniform4f( uniformName, value);
}

int ShaderProgram::setUniform(const std::string &uniformName, Mat4 & value)
{
    addUniform( uniformName );
    setUniformMatrix4fv( uniformName, value);
}

void ShaderProgram::setUniform1f(const std::string &uniformName, float value)
{
    use();
    glUniform1f( uniform( uniformName ), value );
    disable();
}

void ShaderProgram::setUniform3f(const std::string &uniformName, Vec3 value)
{
    use();
    glUniform3f( uniform( uniformName ), value.x, value.y, value.z );
    disable();
}

void ShaderProgram::setUniform4f(const std::string &uniformName, Vec4 value)
{
    use();
    glUniform4f( uniform( uniformName ), value.x, value.y, value.z, value.w );
    disable();
}

void ShaderProgram::setUniformMatrix4fv(const std::string &uniformName, Mat4 value)
{
    use();
    glUniformMatrix4fv( uniform( uniformName ), 1, GL_FALSE, value.get() );
    disable();
}

void ShaderProgram::setUniform1i(const std::string &uniformName, int value)
{
    use();
    glUniform1i( uniform( uniformName ), value );
    disable();
}

}
