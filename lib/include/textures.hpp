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

    void setTexture(const char * uniformName, Texture * texture);

    Texture * texture(const int index);
    Texture * texture(const char * uniformName);
    bool isExistTexture(const int index);
    bool isExistTexture(const char * uniformName);
    const char * textureUniformName(const int index);
    int size();
    ~Textures();

protected:
    std::map<const std::string, Texture *> m_textures;

};

}

#endif /* __TEXTURES_HPP__ */
