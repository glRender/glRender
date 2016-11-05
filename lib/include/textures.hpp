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

    Texture * texture(const int index) const;
    Texture * texture(const char * uniformName) const;
    bool isExistTexture(const int index) const;
    bool isExistTexture(const char * uniformName) const;
    const char * textureUniformName(const int index) const;
    int size() const;

protected:
    std::map<const std::string, Texture *> m_textures;

};

}

#endif /* __TEXTURES_HPP__ */
