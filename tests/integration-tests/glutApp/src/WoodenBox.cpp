#include "WoodenBox.hpp"

namespace glRender {

WoodenBox::WoodenBox()
{    
    std::shared_ptr<Geometry> geometry = GeometryHelper::Box(1.0);

    Textures * textures = new Textures();
    textures->setTexture( "texture0", ResourceManager::instance().textures().get("Plywood_1024x640.png"));

    std::shared_ptr<ShaderProgram> shaderProgram = ResourceManager::instance().shaderPrograms().get("shader0ShP");

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

WoodenBox::~WoodenBox()
{
    delete m_model;
    delete m_aabb;
}

void WoodenBox::update()
{
//    m_model->rotate(0.1, Vec3::AXE_Y());
}

void WoodenBox::draw(Camera * camera)
{
    m_model->draw(camera);
}

Model * WoodenBox::model()
{
    return m_model;
}

IBoundingBox * WoodenBox::bb() const
{
    return m_aabb;
}

}
