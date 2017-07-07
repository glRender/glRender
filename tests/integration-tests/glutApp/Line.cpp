#include "Line.hpp"

#include "geometryBuffer.hpp"

namespace glRender {

Line::Line(Vec3 p0, Vec3 p1, uint segmentsNumber, float r, float g, float b)
    : m_aabb(new AABB(Vec3(0,0,0), 1.0))
    , m_p0(p0)
    , m_p1(p1)
    , m_segmentsNumber(segmentsNumber)
    , m_r(r)
    , m_g(g)
    , m_b(b)
{
//    setSelectable(false);

    Geometry* geometry = GeometryHelper::Line(p0, p1, segmentsNumber);

    Textures * textures = new Textures();

    ShaderProgram * shaderProgram = ResourceManager::getInstance().getShaderProgram("data/colored.vertex", "data/colored.frag");

    shaderProgram->addAttribute<Vec3>("vertex");
    shaderProgram->addAttribute<float>("index");

    shaderProgram->addUniform<Mat4>("projection");
    shaderProgram->addUniform<Mat4>("view");
    shaderProgram->addUniform<Mat4>("model");

    shaderProgram->addUniform<float>("r");
    shaderProgram->addUniform<float>("g");
    shaderProgram->addUniform<float>("b");

    m_model = new Model(geometry, textures, shaderProgram);
    m_model->setWireframeMode(false);
    m_model->setDrawMode(Model::DrawMode::Lines);
    m_model->setOrigin(0.0, 0.0, 0.0);
}

Line::~Line()
{
    delete m_aabb;
}

void Line::update()
{
}

void Line::draw(CameraPtr camera)
{
    m_model->shaderProgram()->setUniform<float>("r", m_r);
    m_model->shaderProgram()->setUniform<float>("g", m_g);
    m_model->shaderProgram()->setUniform<float>("b", m_b);

    m_model->draw(camera);
}

Model * Line::model()
{
    return m_model;
}

IBoundingBox * Line::bb() const
{
    return m_aabb;
}

}