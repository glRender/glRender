#include "model.hpp"

namespace glRender {

Model::Model(Geometry* geometry, Textures* textures, ShaderProgram* shaderProgram) :
    m_geometry(geometry),
    m_shaderProgram(shaderProgram),
    m_textures(textures)
{
    glGenVertexArrays ( 1, &m_vaoId );
    glBindVertexArray ( m_vaoId );
    
    // bind all geometry buffers
    for(int i=0; i < m_geometry->size(); ++i)
    {
        m_geometry->get(i)->bind();
        m_geometry->get(i)->bufferData();
    }
    
    // Set up the Vertex attribute pointer for the vVertex attribute
    for( auto attr : m_shaderProgram->attributeLocList )
    {
        GeometryBuffer* buff = m_geometry->get( attr.first );
        buff->bind();

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

    // add uniforms for every texture
    for (int i = 0; i <m_textures->size(); ++i)
    {
        const std::string textureUniformName = m_textures->textureName( i );
        if ( textureUniformName != "" )
        {
            m_shaderProgram->addUniform( textureUniformName );
        }
    }

    glBindVertexArray ( 0 );

}


Geometry* Model::geometry()
{
    return m_geometry;
}

ShaderProgram* Model::shaderProgram()
{
    return m_shaderProgram;
}

Textures* Model::textures()
{
    return m_textures;
}

void Model::bindTextures()
{
    std::string textureName = "texture";
    for (GLuint i = 0; i < textures()->size(); i++)
    {
        glActiveTexture( GL_TEXTURE0 + i );
        Texture * texture = textures()->texture(i);
        if ( texture != nullptr )
        {
            glBindTexture(GL_TEXTURE_2D, texture->getId() );
            shaderProgram()->setUniform1i( textureName + patch::to_string(i), i );
        }
    }
}

void Model::unbindTextures()
{
    // Always good practice to set everything back to defaults once configured.
    for (GLuint i = 0; i < textures()->size(); ++i)
    {
        glActiveTexture(GL_TEXTURE0 + i);
        glBindTexture(GL_TEXTURE_2D, 0);
    }
}

bool Model::setWireframeMode(bool status)
{
    m_wireframeMode = status;
}

bool Model::isWireframeMode()
{
    return m_wireframeMode;
}

void Model::draw(Camera * camera)
{
    Mat4 view = camera->transformationMatrix();
    shaderProgram()->setUniformMatrix4fv("projection", camera->projectionMatrix());
    shaderProgram()->setUniformMatrix4fv("view", view.invert());
    shaderProgram()->setUniformMatrix4fv("model", transformationMatrix());

    bindTextures();

    shaderProgram()->use();

    if (isWireframeMode())
    {
//          wireframe mode
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    }

    glBindVertexArray ( m_vaoId );

    if (geometry()->isExist("index"))
    {
        GeometryBuffer *indices = geometry()->get("index");
        indices->bind();
        glDrawElements(GL_TRIANGLES, indices->size(), GL_UNSIGNED_INT, 0);

    } else {
        glDrawArrays      ( GL_TRIANGLES, 0, geometry()->get("vertex")->size() );
    }

    glBindVertexArray ( 0 );

    if (isWireframeMode())
    {
//          wireframe mode
        glPolygonMode( GL_FRONT_AND_BACK, GL_FILL );
    }

    shaderProgram()->disable();

    unbindTextures();

}

Model::~Model()
{
    glDeleteVertexArrays(1, &m_vaoId);
    delete m_geometry;
    delete m_shaderProgram;
    delete m_textures;

}
    
}
