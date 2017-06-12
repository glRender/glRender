#include "aabbNodeVisualizator.hpp"

#include "resourceManager.hpp"

namespace glRender {

AABBNodeVisualizator::AABBNodeVisualizator(AABB * aabb) :
    m_aabb(aabb)
{
    std::vector<Vec3> vertices;
    vertices.push_back(Vec3(-0.1f, 0.0f, 0.0f));
    vertices.push_back(Vec3(0.0f, 0.0f, 0.0f));
    vertices.push_back(Vec3(0.0f, 0.0f, -0.1f));
    vertices.push_back(Vec3(0.0f, 0.0f, 0.0f));
    vertices.push_back(Vec3(0.0f, -0.1f, 0.0f));

    Geometry* geometry = new Geometry();
    geometry->set( "vertex", new Buffer<Vec3>( vertices, BufferType::ArrayBuffer) );

    Textures * textures = new Textures();

    std::string vertexShaderCode =
    "\n\
        #version 330 core \n\
        uniform mat4 model; \n\
        uniform mat4 view; \n\
        uniform mat4 projection; \n\
        layout (location = 0) in vec3 vertex; \n\
        void main(void) \n\
        { \n\
           gl_Position      = projection * view * model * vec4 ( vertex, 1.0 ); \n\
        }\n\
    ";

    std::string fragmentShaderCode =
    " \n\
        #version 330 core \n\
        out vec4 color; \n\
        void main(void) \n\
        { \n\
            color = vec4(0.0, 0.0, 0.0, 1.0); \n\
        } \n\
    ";

    ShaderProgram * shaderProgram = ResourceManager::getInstance().getShaderProgram(vertexShaderCode.c_str(), fragmentShaderCode.c_str(), false);
    if (shaderProgram)
    {
        shaderProgram->addAttribute<Vec3>("vertex");

        shaderProgram->addUniform<Mat4>("projection");
        shaderProgram->addUniform<Mat4>("view");
        shaderProgram->addUniform<Mat4>("model");

        m_corner = new Model(geometry, textures, shaderProgram);
        m_corner->setDrawMode(Model::DrawMode::Lines);
        m_corner->setWireframeMode(true);
        m_corner->setOrigin(0.0, 0.0, 0.0);
    }

}

void AABBNodeVisualizator::update()
{
//    m_corner->rotate(1.0f, Vec3(1.0f,0.0f,0.0f));
}

void AABBNodeVisualizator::draw(CameraPtr camera)
{
    Mat4 transforms/* = parentsTransforms()*/;
    Vec3 leftTop0 = m_aabb->origin() + Vec3(-m_aabb->halfSide(), m_aabb->halfSide(), -m_aabb->halfSide());
    m_corner->setOrigin(leftTop0);
    m_corner->draw(camera, transforms);

    Vec3 rightTop0 = m_aabb->origin() + Vec3(m_aabb->halfSide(), m_aabb->halfSide(), -m_aabb->halfSide());
    m_corner->setOrigin(rightTop0);
    m_corner->draw(camera, transforms);

    Vec3 leftBottom0 = m_aabb->origin() + Vec3(-m_aabb->halfSide(), -m_aabb->halfSide(), -m_aabb->halfSide());
    m_corner->setOrigin(leftBottom0);
    m_corner->draw(camera, transforms);

    Vec3 rightBottom0 = m_aabb->origin() + Vec3(m_aabb->halfSide(), -m_aabb->halfSide(), -m_aabb->halfSide());
    m_corner->setOrigin(rightBottom0);
    m_corner->draw(camera, transforms);

    Vec3 leftTop1 = m_aabb->origin() + Vec3(-m_aabb->halfSide(), m_aabb->halfSide(), -m_aabb->halfSide());
    m_corner->setOrigin(leftTop1);
    m_corner->draw(camera, transforms);

    Vec3 rightTop1 = m_aabb->origin() + Vec3(m_aabb->halfSide(), m_aabb->halfSide(), -m_aabb->halfSide());
    m_corner->setOrigin(rightTop1);
    m_corner->draw(camera, transforms);

    Vec3 leftBottom1 = m_aabb->origin() + Vec3(-m_aabb->halfSide(), -m_aabb->halfSide(), -m_aabb->halfSide());
    m_corner->setOrigin(leftBottom1);
    m_corner->draw(camera, transforms);

    Vec3 rightBottom1 = m_aabb->origin() + Vec3(m_aabb->halfSide(), -m_aabb->halfSide(), -m_aabb->halfSide());
    m_corner->setOrigin(rightBottom1);
    m_corner->draw(camera, transforms);
}

}
