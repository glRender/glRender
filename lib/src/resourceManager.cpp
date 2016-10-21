#include "resourceManager.hpp"

namespace glRender {

glRender::Texture *glRender::ResourceManager::getTexture(const char * path)
{
    std::string key = std::string(path);
    if (m_textures.find(key) == m_textures.end())
    {
        m_textures[key] = new Texture(path);
    }

    return m_textures.at(key);
}

}
