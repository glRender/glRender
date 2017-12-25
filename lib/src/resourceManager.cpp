#include "resourceManager.hpp"

#include "shader.hpp"
#include "shaderProgram.hpp"
#include "texture.hpp"
#include "textures.hpp"

using namespace glRender;

ResourceManager::ResourceManager()
{
}

ResourceManager &ResourceManager::instance()
{
    static ResourceManager instance;
    return instance;
}

ResourceCache<Texture> &ResourceManager::textures()
{
    return m_textureCache;
}

ResourceCache<ShaderProgram> &ResourceManager::shaderPrograms()
{
    return m_shaderProgramsChache;
}
