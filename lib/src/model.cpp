#include "model.hpp"
#include "opengl.h"

namespace glRender {

Model::Model(Geometry* geometry, Textures* textures, ShaderProgram* shaderProgram) :
    m_geometry(geometry),
    m_shaderProgram(shaderProgram),
    m_textures(textures)
{
    glGenVertexArrays ( 1, &m_vaoId );
    glBindVertexArray ( m_vaoId );

    if (geometry->hasIndices())
    {
        m_indicesBuffer = new Buffer<uint32_t>(geometry->getIndices(), BufferType::ElementArrayBuffer);
    }

    m_shaderProgram->fillAttributes(m_geometry);
    glBindVertexArray ( 0 );

}

void Model::setWireframeMode(bool status)
{
    m_wireframeMode = status;
}

bool Model::isWireframeMode()
{
    return m_wireframeMode;
}

void Model::setDrawMode(Model::DrawMode drawMode)
{
    m_drawMode = drawMode;
}

Model::DrawMode Model::drawMode()
{
    return m_drawMode;
}

void Model::draw(CameraPtr camera)
{
    glBindVertexArray ( m_vaoId );

    m_shaderProgram->use();

    if (!m_textures->isEmpty())
    {
        m_shaderProgram->bindTextures(m_textures);
    }

    glUniformMatrix4fv( m_shaderProgram->uniform<Mat4>( "projection" ), 1, GL_FALSE, camera->projectionMatrix().get() );
    glUniformMatrix4fv( m_shaderProgram->uniform<Mat4>( "view" ),       1, GL_FALSE, camera->transformationMatrix().get() );
    glUniformMatrix4fv( m_shaderProgram->uniform<Mat4>( "model" ),      1, GL_FALSE, transformationMatrix().get() );

    if (m_wireframeMode) { glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); }

    if (m_indicesBuffer != nullptr)
    {
        glDrawElements(m_drawMode, m_indicesBuffer->size(), GL_UNSIGNED_INT, (void*)(0));
    } else if (m_geometry->has("vertex"))
    {
        glDrawArrays(m_drawMode, 0, m_geometry->get("vertex")->size());
    }

    if (m_wireframeMode) { glPolygonMode( GL_FRONT_AND_BACK, GL_FILL ); }

    if (!m_textures->isEmpty())
    {
        shaderProgram()->unbindTextures();
    }

    shaderProgram()->disable();

    glBindVertexArray ( 0 );
}

void Model::draw(CameraPtr camera, Mat4 transforms)
{
    glBindVertexArray ( m_vaoId );

    m_shaderProgram->use();

    if (!m_textures->isEmpty())
    {
        m_shaderProgram->bindTextures(m_textures);
    }

    glUniformMatrix4fv( m_shaderProgram->uniform<Mat4>( "projection" ), 1, GL_FALSE, camera->projectionMatrix().get() );
    glUniformMatrix4fv( m_shaderProgram->uniform<Mat4>( "view" ),       1, GL_FALSE, camera->transformationMatrix().get() );
    glUniformMatrix4fv( m_shaderProgram->uniform<Mat4>( "model" ),      1, GL_FALSE, (transforms * transformationMatrix()).get() );

    if (m_wireframeMode) { glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); }

    if (m_indicesBuffer != nullptr)
    {
        glDrawElements(m_drawMode, m_indicesBuffer->size(), GL_UNSIGNED_INT, (void*)(0));
    } else if (m_geometry->has("vertex"))
    {
        glDrawArrays(m_drawMode, 0, m_geometry->get("vertex")->size());
    }

    if (m_wireframeMode) { glPolygonMode( GL_FRONT_AND_BACK, GL_FILL ); }

    if (!m_textures->isEmpty())
    {
        shaderProgram()->unbindTextures();
    }

    shaderProgram()->disable();

    glBindVertexArray ( 0 );
}

Model::~Model()
{
    delete m_geometry;
    delete m_shaderProgram;
    delete m_textures;
    glDeleteVertexArrays(1, &m_vaoId);
}
    
}
