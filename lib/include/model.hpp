#ifndef __MODEL_HPP__		
#define __MODEL_HPP__

#include "base.h"

#include "positionable.hpp"
#include "geometry.hpp"
#include "shaderProgram.hpp"
#include "camera.hpp"
#include "textures.hpp"

namespace glRender
{

class Model : public Positionable
{
public:
    enum DrawMode
    {
        Triangles = GL_TRIANGLES,
        Points = GL_POINTS,
        Lines = GL_LINE_STRIP
    };

    Model(Geometry* geometry, Textures* textures, ShaderProgram* shaderProgram);
    ~Model();

    void draw(Camera * camera);
    
    Geometry * geometry();
    ShaderProgram * shaderProgram();
    Textures * textures();

    void bindTextures();
    void unbindTextures();

    bool setWireframeMode(bool status);
    bool isWireframeMode();

    bool setDrawMode(DrawMode drawMode);
    DrawMode drawMode();

private:
    Geometry * m_geometry;
    ShaderProgram * m_shaderProgram;
    Textures * m_textures;

    bool m_wireframeMode = false;

    GLuint m_vaoId;
    DrawMode m_drawMode = DrawMode::Triangles;

};

}

#endif /* __MODEL_HPP__ */
