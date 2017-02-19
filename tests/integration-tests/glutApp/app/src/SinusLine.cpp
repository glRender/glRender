#include "SinusLine.hpp"

#include "geometryBuffer.hpp"

namespace glRender {

SinusLine::SinusLine(Vec3 p0, Vec3 p1, uint segmentsNumber, float r, float g, float b)
    : m_aabb(new AABB(Vec3(0,0,0), 1.0))
    , m_p0(p0)
    , m_p1(p1)
    , m_segmentsNumber(segmentsNumber)
    , m_r(r)
    , m_g(g)
    , m_b(b)
{
    setSelectable(false);

    std::vector<Vec3> vertices;
    std::vector<float> indexes;

    float step = 1.0 / m_segmentsNumber;
    Vec3 pn = m_p1 - m_p0;

    for (float t=0.0; t<=1.0; t+=step)
    {
        Vec3 p = p0 + pn * t;
        vertices.push_back(p);
    }

    int lineLength = m_segmentsNumber;

    for (int i = 0; i<m_segmentsNumber; i++)
    {
        float opacity = 1;
        if (i <= lineLength)
        {
            opacity = i / static_cast<float>(lineLength);
        }
        else
        {
            opacity = 0.0;
        }
        indexes.push_back(opacity);
    }

    Geometry* geometry = new Geometry();
    geometry->set( "vertex", new Buffer<Vec3>( vertices, BufferType::ArrayBuffer) );
    geometry->set( "index", new Buffer<float>( indexes, BufferType::ArrayBuffer) );

    Textures * textures = new Textures();

    ShaderProgram * shaderProgram = ResourceManager::getInstance().getShaderProgram("data/transparentPoints.vertex", "data/transparentPoints.frag");

    shaderProgram->addAttribute<Vec3>("vertex");
    shaderProgram->addAttribute<float>("index");

    shaderProgram->addUniform<Mat4>("projection");
    shaderProgram->addUniform<Mat4>("view");
    shaderProgram->addUniform<Mat4>("model");

    shaderProgram->addUniform<float>("r");
    shaderProgram->addUniform<float>("g");
    shaderProgram->addUniform<float>("b");

    shaderProgram->addUniform<Vec3>("p0");
    shaderProgram->addUniform<Vec3>("p1");
    shaderProgram->addUniform<float>("offset");

    m_model = new Model(geometry, textures, shaderProgram);
    m_model->setWireframeMode(false);
    m_model->setDrawMode(Model::DrawMode::Lines);
    m_model->setOrigin(0.0, 0.0, 0.0);

    offset = (rand() % 255) / 255.0;
}

SinusLine::~SinusLine()
{
    delete m_aabb;
}

void SinusLine::update()
{
    Vec3 dir = m_p1 - m_p0;
    Vec3 moveDir = dir.cross(m_p0);
    moveDir.normalize();

    AbstractBuffer * b = model()->geometry()->get("vertex");
    Buffer<Vec3> * a = dynamic_cast<Buffer<Vec3> *>(b);

    offset += 0.05;

    float step = 1.0 / m_segmentsNumber;
    Vec3 pn = m_p1 - m_p0;

    std::vector<Vec3> v;
    for (float t=0.0; t<=1.0; t+=step)
    {
        Vec3 p = m_p0 + pn * t + moveDir * sin(offset + 50 * t);
        v.push_back(p);
    }
    a->rewrite(0, v);

//    m_model->rotate(0.1, Vec3::AXE_Y());
}

void SinusLine::draw(Camera *camera)
{
    m_model->shaderProgram()->setUniform<float>("r", m_r);
    m_model->shaderProgram()->setUniform<float>("g", m_g);
    m_model->shaderProgram()->setUniform<float>("b", m_b);

    m_model->shaderProgram()->setUniform<Vec3>("p0", m_p0);
    m_model->shaderProgram()->setUniform<Vec3>("p1", m_p1);

    m_model->shaderProgram()->setUniform<float>("offset", offset);

    m_model->draw(camera);
}

Model * SinusLine::model()
{
    return m_model;
}

IBoundingBox * SinusLine::bb()
{
    return m_aabb;
}

}
