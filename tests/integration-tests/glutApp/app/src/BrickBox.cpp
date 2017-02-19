#include "BrickBox.hpp"

namespace glRender {

BrickBox::BrickBox()
{
    Geometry * geometry = GeometryHelper::Cube(1.0);

    Textures * textures = new Textures();
    textures->setTexture( "texture0", ResourceManager::getInstance().getTexture("data/TexturesCom_BricksSmallOld0080_1_seamless_S_1024x1024.png") );
    textures->setTexture( "texture1", ResourceManager::getInstance().getTexture("data/Plywood_1024x640.png") );

    ShaderProgram * shaderProgram = ResourceManager::getInstance().getShaderProgram("data/shader0.vertex", "data/shader0.frag");
    shaderProgram->addAttribute<Vec3>("vertex");
    shaderProgram->addAttribute<Vec2>("uv");

    shaderProgram->addUniform<Mat4>("projection");
    shaderProgram->addUniform<Mat4>("view");
    shaderProgram->addUniform<Mat4>("model");
    shaderProgram->addUniform<Texture>("texture0");

    m_model = new Model(geometry, textures, shaderProgram);
    m_model->setWireframeMode(false);
    m_model->setOrigin(0.0, 0.0, 0.0);
}

BrickBox::~BrickBox()
{
    delete m_model;
    delete m_aabb;
}

void BrickBox::update()
{
//    m_model->rotate(0.1, Vec3::AXE_Y());
}

void BrickBox::draw(Camera *camera)
{
    m_model->draw(camera);
}

Model * BrickBox::model()
{
    return m_model;
}

AABB *BrickBox::bb()
{
    return m_aabb;
}

}
