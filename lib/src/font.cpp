#include "font.hpp"

#include "shader.hpp"
#include "shaderProgram.hpp"
#include "texture.hpp"
#include "resourceManager.hpp"

using namespace glRender;

Font::Font(std::shared_ptr<Texture> texture, const TextureFontInformation &information)
    : m_texture(texture)
    , m_information(information)
{
//    m_shaderProgram = ResourceManager::getInstance().shaderPrograms().get(uuid, )
}

Font::Font(const char * pathToTexture, const char * pathToTextureFontInfo)
{
//    m_texture = ResourceManager::getInstance().textures().get("*", pathToTexture);

//    m_shaderProgram = ResourceManager::getInstance().shaderPrograms().get(uuid, m_vertexShaderText, m_fragmentShaderText, false);
}
