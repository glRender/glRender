#include "QuadraticBezeirCurve.hpp"

namespace glRender {

QuadraticBezeirCurve::QuadraticBezeirCurve(Vec3 p0, Vec3 p1, Vec3 p2, uint segmentsNumber, Vec3 color)
    : m_aabb(new AABB(Vec3(0,0,0), 1.0))
    , m_p0(p0)
    , m_p1(p1)
    , m_p2(p2)
    , m_segmentsNumber(segmentsNumber)
    , m_color(color)
    , m_speed((double) rand() / (RAND_MAX) * 0.01)
{
//    setSelectable(false);
    Geometry * geometry = GeometryHelper::QuadraticBezierCurve(p0, p1, p2, segmentsNumber);
\
    Textures * textures = new Textures();

//    std::shared_ptr<ShaderProgram> shaderProgram = ResourceManager::getInstance().shaderPrograms().get("*", "data/colored.vertex", "data/colored.frag");

    std::shared_ptr<ShaderProgram> shaderProgram = ResourceManager::instance().shaderPrograms().get("coloredShP");

    shaderProgram->addAttribute<Vec3>("vertex");

    shaderProgram->addUniform<Mat4>("projection");
    shaderProgram->addUniform<Mat4>("view");
    shaderProgram->addUniform<Mat4>("model");
    // shaderProgram->addUniform<float>("r");
    // shaderProgram->addUniform<float>("g");
    // shaderProgram->addUniform<float>("b");
    shaderProgram->setUniform<Vec3>("color", m_color);

    shaderProgram->setUniform<Vec3>("color", m_color);

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
    m_model->rotate(m_speed, Vec3::AXE_Y());
}

void QuadraticBezeirCurve::draw(Camera * camera)
{
    m_model->shaderProgram()->setUniform<Vec3>("color", m_color);
    m_model->setParentsMatrix(globalTransforms());

    m_model->draw(camera);
}

Model * QuadraticBezeirCurve::model()
{
    return m_model;
}

IBoundingBox * QuadraticBezeirCurve::bb() const
{
    return m_aabb;
}

}

