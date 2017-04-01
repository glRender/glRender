#include "textures.hpp"

namespace glRender {

Textures::Textures()
{

}

void Textures::setTexture(const char * uniformName, Texture * texture)
{
    m_textures[uniformName] = texture;
    
}

Texture* Textures::texture(const char * uniformName) const
{
    auto it = m_textures.find( uniformName );
    if ( it != m_textures.end() )
    {
        return it->second;
    }
    else
    {
        return nullptr;
    }

}

Texture* Textures::texture(const uint32_t index) const
{
    if (m_textures.size() > index)
    {
        auto it = m_textures.begin();
        for(uint32_t i=0; i<index; i++)
        {
            it++;
        }

        return it->second;
    }
    else
    {
        return nullptr;
    }
}

bool Textures::isExistTexture(const uint32_t index) const
{
    if (m_textures.size() > index)
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool Textures::isExistTexture(const char * uniformName) const
{
    auto it = m_textures.find( uniformName );
    if ( it != m_textures.end() )
    {
        return true;
    }
    else
    {
        return false;
    }

}

const char * Textures::textureUniformName(const uint32_t index) const
{
    if (isExistTexture(index))
    {
        auto it = m_textures.begin();
        for(uint32_t i=0; i<index; i++)
        {
            it++;
        }

        return it->first.c_str();

    }
    else
    {
        return "";
    }
}






Textures::~Textures()
{
    for (auto item : m_textures)
    {
        delete item.second;
    }
}

}
