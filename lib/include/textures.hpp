#ifndef __TEXTURES_HPP__		
#define __TEXTURES_HPP__

#include "base.h"

#include "texture.hpp"

namespace glRender
{

class Textures
{
public:
    Textures();
    ~Textures();

    void setTexture(const char * uniformName, Texture * texture);

    Texture * texture(const uint32_t index) const;
    Texture * texture(const char * uniformName) const;
    bool isExistTexture(const uint32_t index) const;
    bool isExistTexture(const char * uniformName) const;
    const char * textureUniformName(const uint32_t index) const;

    inline int size() const
    {
        return m_textures.size();
    }

    inline bool isEmpty() const
    {
        return m_textures.size() == 0;
    }

protected:
    std::map<const std::string, Texture *> m_textures;

};

}

#endif /* __TEXTURES_HPP__ */
