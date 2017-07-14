#include "model.hpp"
#include "opengl.h"

namespace glRender {

Model::Model(Geometry* geometry, Textures* textures, std::shared_ptr<ShaderProgram> shaderProgram) :
    m_geometry(geometry),
    m_shaderProgramSrtPtr(shaderProgram),
    m_shaderProgram(shaderProgram.get()),
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

    glBindVertexArray ( m_vaoId );

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

//const Mat4 & Model::localGlobalMatrix() const
//{
//    return m_localGlobalMatrix;
//}

//void Model::setLocalMatrix(Mat4 & m)
//{
//    m_localMatrix = m;
//    m_localGlobalMatrix = m_localMatrix * m_globalMatrix;
//}

//void Model::setGlobalMatrix(Mat4 && m)
//{
//    m_globalMatrix = m;
//    m_localGlobalMatrix = m_localMatrix * m_globalMatrix;
//}

//const Mat4 & Model::localMatrix() const
//{
//    return m_localMatrix;
//}

//const Mat4 & Model::globalMatrix() const
//{
//    return m_globalMatrix;
//}

void Model::draw(Camera * camera)
{
    glBindVertexArray ( m_vaoId );

    m_shaderProgram->use();

    if (!m_textures->isEmpty())
    {
        m_shaderProgram->bindTextures(m_textures);
    }

    glUniformMatrix4fv( m_shaderProgram->uniform<Mat4>( "projection" ), 1, GL_FALSE, camera->projectionMatrix().get() );
    glUniformMatrix4fv( m_shaderProgram->uniform<Mat4>( "view" ),       1, GL_FALSE, camera->globalMatrix().get() );
    glUniformMatrix4fv( m_shaderProgram->uniform<Mat4>( "model" ),      1, GL_FALSE, globalMatrix().get() );

    if (m_wireframeMode) { glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); }

    if (m_indicesBuffer != nullptr)
    {
        glDrawElements(m_drawMode, m_indicesBuffer->size(), GL_UNSIGNED_INT, (void*)(0));
    } else if (m_geometry->has("vertex"))
    {
        glDrawArrays(m_drawMode, 0, m_geometry->get("vertex")->size());
    }

    if (m_wireframeMode) { glPolygonMode( GL_FRONT_AND_BACK, GL_FILL ); }

//    if (!m_textures->isEmpty())
//    {
//        shaderProgram()->unbindTextures();
//    }

//    shaderProgram()->disable();

//    glBindVertexArray ( 0 );
}

//void Model::draw(CameraPtr camera, Mat4 transforms)
//{
//    glBindVertexArray ( m_vaoId );

//    m_shaderProgram->use();

//    if (!m_textures->isEmpty())
//    {
//        m_shaderProgram->bindTextures(m_textures);
//    }

//    glUniformMatrix4fv( m_shaderProgram->uniform<Mat4>( "projection" ), 1, GL_FALSE, camera->projectionMatrix().get() );
//    glUniformMatrix4fv( m_shaderProgram->uniform<Mat4>( "view" ),       1, GL_FALSE, camera->localGlobalMatrix().get() );
//    glUniformMatrix4fv( m_shaderProgram->uniform<Mat4>( "model" ),      1, GL_FALSE, ( /*transforms * transformationMatrix*/localGlobalMatrix()).get() );

//    if (m_wireframeMode) { glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); }

//    if (m_indicesBuffer != nullptr)
//    {
//        glDrawElements(m_drawMode, m_indicesBuffer->size(), GL_UNSIGNED_INT, (void*)(0));
//    } else if (m_geometry->has("vertex"))
//    {
//        glDrawArrays(m_drawMode, 0, m_geometry->get("vertex")->size());
//    }

//    if (m_wireframeMode) { glPolygonMode( GL_FRONT_AND_BACK, GL_FILL ); }

//    if (!m_textures->isEmpty())
//    {
//        shaderProgram()->unbindTextures();
//    }

//    shaderProgram()->disable();

//    glBindVertexArray ( 0 );
//}

Model::~Model()
{
    delete m_geometry;
    delete m_textures;
    glDeleteVertexArrays(1, &m_vaoId);
}
    
}
