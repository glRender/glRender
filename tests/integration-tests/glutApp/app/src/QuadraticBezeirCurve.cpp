#include "QuadraticBezeirCurve.hpp"

namespace glRender {

QuadraticBezeirCurve::QuadraticBezeirCurve(Vec3 p0, Vec3 p1, Vec3 p2, uint segmentsNumber, float r, float g, float b)
    : m_aabb(new AABB(Vec3(0,0,0), 1.0))
    , m_p0(p0)
    , m_p1(p1)
    , m_p2(p2)
    , m_segmentsNumber(segmentsNumber)
    , m_r(r)
    , m_g(g)
    , m_b(b)
{
    setSelectable(false);
    Geometry * geometry = GeometryHelper::QuadraticBezierCurve(p0, p1, p2, segmentsNumber);
\
    Textures * textures = new Textures();

    ShaderProgram * shaderProgram = ResourceManager::getInstance().getShaderProgram("data/colored.vertex", "data/colored.frag");
    shaderProgram->addAttribute<Vec3>("vertex");

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

QuadraticBezeirCurve::~QuadraticBezeirCurve()
{
    delete m_aabb;
}

void QuadraticBezeirCurve::update()
{

//    m_model->rotate(0.1, Vec3::AXE_Y());
}

void QuadraticBezeirCurve::draw(Camera *camera)
{
    m_model->shaderProgram()->setUniform<float>("r", m_r);
    m_model->shaderProgram()->setUniform<float>("g", m_g);
    m_model->shaderProgram()->setUniform<float>("b", m_b);

    m_model->draw(camera);
}

Model * QuadraticBezeirCurve::model()
{
    return m_model;
}

IBoundingBox * QuadraticBezeirCurve::bb()
{
    return m_aabb;
}

}

