#pragma once

#include "base.h"
#include "positionable.hpp"

namespace glRender
{

class Geometry;
class ShaderProgram;
class Camera;
class Textures;
class AbstractBuffer;

class Model : public Positionable
{
public:
    enum DrawMode
    {
        Triangles = 0x0004 /*GL_TRIANGLES*/,
        Points = 0x0000 /*GL_POINTS*/,
        Lines = 0x0003 /*GL_LINE_STRIP*/
    };

    Model();
    Model(std::shared_ptr<Geometry> geometry, Textures* textures, std::shared_ptr<ShaderProgram> shaderProgram);

    virtual ~Model();

    virtual void draw(Camera * camera);

    inline std::shared_ptr<Geometry> geometry()
    {
        return m_geometry;
    }

    void setGeometry(std::shared_ptr<Geometry> geometry);
    void setTextures(Textures * textures);
    void setShaderProgram(std::shared_ptr<ShaderProgram> program);

    inline ShaderProgram * shaderProgram()
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

private:
    uint32_t m_vaoId;

    std::shared_ptr<Geometry> m_geometry;
    std::shared_ptr<ShaderProgram> m_shaderProgramSrtPtr;
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
