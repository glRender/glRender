#include "textures.hpp"

namespace glRender {

Textures::Textures()
{

}

void Textures::setTexture(const std::string& uniformName, Texture* texture)
{
    m_textures[uniformName] = texture;
    
}

Texture* Textures::texture(const std::string& uniformName)
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

bool Textures::isExistTexture(const int index)
{
    if ( m_textures.size() > index && index >= 0 )
    {
        return true;
    }
    else
    {
        return false;
    }
}

Texture* Textures::texture(const int index)
{
    if ( m_textures.size() > index && index >= 0 )
    {
        auto it = m_textures.begin();
        for(int i=0; i<index; i++)
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

const std::string Textures::textureName(const int index)
{
    if ( isExistTexture( index ) )
    {
        auto it = m_textures.begin();
        for(int i=0; i<index; i++)
        {
            it++;
        }

        return it->first;

    }
    else
    {
        return "";
    }
}

Textures::~Textures()
{

}

int Textures::size()
{
    return m_textures.size();
}

}
