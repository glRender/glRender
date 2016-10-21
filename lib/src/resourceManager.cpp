#include "resourceManager.hpp"

namespace glRender {

glRender::Texture *glRender::ResourceManager::getTexture(std::string path)
{
    if (m_textures.find(path) == m_textures.end())
    {
        m_textures[path] = new Texture(path.c_str());
    }

    return m_textures.at(path);
}

}
