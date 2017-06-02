#include "aabbNodeVisualizator.hpp"

#include "resourceManager.hpp"

namespace glRender {

AABBNodeVisualizator::AABBNodeVisualizator(AABB * aabb) :
    m_aabb(aabb)
{
    std::vector<Vec3> vertices;
    vertices.push_back(Vec3(-0.1f, 0.0f, 0.0f));
    vertices.push_back(Vec3(0.0f, 0.0f, 0.0f));
    vertices.push_back(Vec3(0.0f, 0.0f, -1.0f));
    vertices.push_back(Vec3(0.0f, 0.0f, 0.0f));
    vertices.push_back(Vec3(0.1f, 0.0f, 0.0f));

    Geometry* geometry = new Geometry();
    geometry->set( "vertex", new Buffer<Vec3>( vertices, BufferType::ArrayBuffer) );

    Textures * textures = new Textures();

    std::string vertexShaderCode =
    "\
    ";

    std::string fragmentShaderCode =
    "\
    ";

    ShaderProgram * shaderProgram = ResourceManager::getInstance().getShaderProgram(vertexShaderCode.c_str(), fragmentShaderCode.c_str(), false);
    if (shaderProgram)
    {
        shaderProgram->addAttribute<Vec3>("vertex");

        shaderProgram->addUniform<Mat4>("projection");
        shaderProgram->addUniform<Mat4>("view");
        shaderProgram->addUniform<Mat4>("model");

        m_corner = new Model(geometry, textures, shaderProgram);
        m_corner->setWireframeMode(true);
        m_corner->setOrigin(0.0, 0.0, 0.0);
    }

}

void AABBNodeVisualizator::update()
{
}

void AABBNodeVisualizator::draw(CameraPtr camera)
{
}

}
