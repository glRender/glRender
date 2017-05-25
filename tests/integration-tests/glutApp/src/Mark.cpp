#include "Mark.hpp"

namespace glRender {

Mark::Mark(float r, float g, float b, float size)
    : m_aabb(new AABB(Vec3(0,0,0), size))
    , m_r(r)
    , m_g(g)
    , m_b(b)
{
//    setSelectable(true);
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

    m_model->draw(camera, parentsTransforms());
}

bool Mark::intersects(const Ray *ray) const
{
    return m_aabb->intersects(ray);
}

Model * Mark::model() const
{
    return m_model;
}

IBoundingBox * Mark::bb() const
{
    return m_aabb;
}

void Mark::onSelect(Ray * ray, Camera * camera)
{
    changeColor();

    Vec3 n = camera->front();
    Vec3 M1 = camera->position();
    Vec3 M2 = model()->origin();

    float D1 = -(n.x*M1.x + n.y*M1.y + n.z*M1.z);
    float D2 = -(n.x*M2.x + n.y*M2.y + n.z*M2.z);

    float top = fabs(D2-D1);
    float bottom = sqrt( pow(n.x, 2) +
                         pow(n.y, 2) +
                         pow(n.z, 2) );

    float distance = bb()->origin().distance(camera->position());
    distance = top / bottom;

    std::cout << "Selected!" << std::endl;
    printf("The distance to plane of camera: %f\n", distance);
    std::cout << "" << std::endl;

}

void Mark::onMove(Vec3 & toPosition)
{
    model()->setOrigin(toPosition);
    bb()->setOrigin(toPosition);

    printf("New position: %f, %f, %f\n", toPosition.x, toPosition.y, toPosition.z);
    std::cout << "" << std::endl;

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


