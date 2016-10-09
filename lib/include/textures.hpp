#ifndef __TEXTURES_HPP__		
#define __TEXTURES_HPP__

#include "base.h"

#include "texture.hpp"

namespace glRender
{

class Textures
{
protected:
    std::map<const std::string, Texture *> m_textures;

public:
	Textures();

    void setTexture(const char * uniformName, Texture * texture);
	
    Texture * texture(const char * uniformName);
    bool isExistTexture(const int index);
    Texture * texture(const int index);
    const char * textureName(const int index);
	int size();

    ~Textures();

};

}

#endif /* __TEXTURES_HPP__ */
