#ifndef __MODEL_HPP__		
#define __MODEL_HPP__

#include "base.h"

#include "positionable.hpp"
#include "geometry.hpp"
#include "shaderProgram.hpp"
#include "camera.hpp"
#include "textures.hpp"
#include "geometryBuffer.hpp"

namespace glRender
{

class Model : public Positionable
{
public:
    enum DrawMode
    {
        Triangles = 0x0004 /*GL_TRIANGLES*/,
        Points = 0x0000 /*GL_POINTS*/,
        Lines = 0x0003 /*GL_LINE_STRIP*/
    };

    Model(Geometry* geometry, Textures* textures, ShaderProgram* shaderProgram);
    ~Model();

    void draw(Camera * camera);
//    void draw(CameraPtr camera, Mat4 transforms);

    inline Geometry* geometry()
    {
        return m_geometry;
    }

    inline ShaderProgram* shaderProgram()
    {
        return m_shaderProgram;
    }

    inline Textures* textures()
    {
        return m_textures;
    }

    void setWireframeMode(bool status);
    bool isWireframeMode();

    void setDrawMode(DrawMode drawMode);
    DrawMode drawMode();

//    void setLocalMatrix(Mat4 & m);
//    void setGlobalMatrix(Mat4 && m);

//    const Mat4 & localMatrix() const;
//    const Mat4 & globalMatrix() const;
//    const Mat4 & localGlobalMatrix() const;

private:
    uint32_t m_vaoId;

    Geometry * m_geometry;
    ShaderProgram * m_shaderProgram;
    Textures * m_textures;

    AbstractBuffer * m_indicesBuffer = nullptr;

    DrawMode m_drawMode = DrawMode::Triangles;
    bool m_wireframeMode = false;

    Mat4 m_localMatrix;
    Mat4 m_parentsMatrix;
    Mat4 m_globalMatrix;
};

}

#endif /* __MODEL_HPP__ */
