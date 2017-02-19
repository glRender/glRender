#include "Mark.hpp"

namespace glRender {

Mark::Mark(float r, float g, float b, float size)
    : m_aabb(new AABB(Vec3(0,0,0), size))
    , m_r(r)
    , m_g(g)
    , m_b(b)
{
    setSelectable(true);
    Geometry * geometry = GeometryHelper::Cube(size);

    Textures * textures = new Textures();

    ShaderProgram * shaderProgram = ResourceManager::getInstance().getShaderProgram("data/colored.vertex", "data/colored.frag");
//    ShaderProgram * shaderProgram = new ShaderProgram("data/colored.vertex", "data/colored.frag");
    shaderProgram->addAttribute<Vec3>("vertex");

    shaderProgram->addUniform<Mat4>("projection");
    shaderProgram->addUniform<Mat4>("view");
    shaderProgram->addUniform<Mat4>("model");
    shaderProgram->addUniform<float>("r");
    shaderProgram->addUniform<float>("g");
    shaderProgram->addUniform<float>("b");

    m_model = new Model(geometry, textures, shaderProgram);
    m_model->setWireframeMode(false);
    m_model->setOrigin(0.0, 0.0, 0.0);
}

Mark::~Mark()
{
    delete m_aabb;
}

void Mark::update()
{
//    m_model->rotate(0.1, Vec3::AXE_Y());
}

void Mark::draw(Camera *camera)
{
    m_model->shaderProgram()->setUniform<float>("r", m_r);
    m_model->shaderProgram()->setUniform<float>("g", m_g);
    m_model->shaderProgram()->setUniform<float>("b", m_b);

    m_model->draw(camera);
}

Model * Mark::model()
{
    return m_model;
}

IBoundingBox * Mark::bb()
{
    return m_aabb;
}

void Mark::changeColor()
{
    if (m_r == 1 && m_g == 0 && m_b == 0)
    {
        m_r = 0;
        m_g = 1;
        m_b = 0;
    }
    else if (m_r == 0 && m_g == 1 && m_b == 0)
    {
        m_r = 1;
        m_g = 0;
        m_b = 0;
    }
}

}


