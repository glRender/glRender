#include "Mark.hpp"

namespace glRender {

Mark::Mark(Vec3 color, float size, uint i, uint j, uint k)
    : m_aabb(new AABB(Vec3(0,0,0), size))
    , m_color(color)
    , m_i(i)
    , m_j(j)
    , m_k(k)
{
    Geometry * geometry = GeometryHelper::Box(size);

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

    shaderProgram->setUniform<float>("r", m_color.x);
    shaderProgram->setUniform<float>("g", m_color.y);
    shaderProgram->setUniform<float>("b", m_color.z);

    m_model = new Model(geometry, textures, shaderProgram);
    m_model->setWireframeMode(true);
    m_model->setOrigin(0.0, 0.0, 0.0);

    m_model->setOrigin(Vec3(i * 3, j * 3 - 25, k * 3 - 25));
    m_aabb->setOrigin(m_model->origin());
}

Mark::~Mark()
{
    delete m_aabb;
}

void Mark::update()
{
//    m_model->rotate(0.1, Vec3::AXE_Y());
}

void Mark::draw(CameraPtr camera)
{
    m_model->shaderProgram()->setUniform<float>("r", m_color.x);
    m_model->shaderProgram()->setUniform<float>("g", m_color.y);
    m_model->shaderProgram()->setUniform<float>("b", m_color.z);

    m_model->draw(camera, parentsTransforms());
}

bool Mark::intersects(const RayPtr ray) const
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

void Mark::onMouseDown(RayPtr ray, CameraPtr camera)
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

    m_isSelected = true;

    std::cout << "Selected!" << std::endl;
    printf("The distance to plane of camera: %f\n", distance);
    std::cout << "" << std::endl;

}

void Mark::onMouseUp(RayPtr ray, CameraPtr camera)
{
    m_isSelected = false;
}

void Mark::onMouseMove(Vec3 & toPosition)
{
    model()->setOrigin(toPosition);
    bb()->setOrigin(toPosition);

    printf("New position: %f, %f, %f\n", toPosition.x, toPosition.y, toPosition.z);
    std::cout << "" << std::endl;

}

void Mark::changeColor()
{
    if (m_color.x == 1 && m_color.y == 0 && m_color.z == 0)
    {
        m_color.set(0,1,0);
    }
    else if (m_color.x == 0 && m_color.y == 1 && m_color.z == 0)
    {
        m_color.set(1,0,0);
    }

}

}


