#include "font.hpp"

#include "shader.hpp"
#include "shaderProgram.hpp"
#include "texture.hpp"
#include "resourceManager.hpp"
#include "geometryHelper.hpp"
#include "model.hpp"

using namespace glRender;

Font::Font(std::shared_ptr<Texture> texture, const TextureFontInformation &information)
    : m_texture(texture)
    , m_information(information)
{
    Geometry * geometry = GeometryHelper::Plane(Vec3(-0.5, 0.5, -0.5), Vec3(0.5, 0.5, -0.5), Vec3(-0.5, -0.5, -0.5), Vec3(0.5, -0.5, -0.5));

    Textures * textures = new Textures();
    textures->setTexture("texture", m_texture);

    ResourceManager::instance().shaderPrograms().create("fontShaderProgram", [this]() {
        std::map<ShaderType, const char *> shadersTexts = {
            {ShaderType::VertexShader, m_vertexShaderCode.c_str()},
            {ShaderType::FragmentShader, m_fragmentShaderCode.c_str()}
        };
        return createShaderProgramFromText(shadersTexts);
    });
    m_shaderProgram = ResourceManager::instance().shaderPrograms().get("fontShaderProgram");
    m_model = new Model(geometry, textures, m_shaderProgram);
}
