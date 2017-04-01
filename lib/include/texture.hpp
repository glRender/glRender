#ifndef __TEXTURE_HPP__		
#define __TEXTURE_HPP__

#include "base.h"
#include "image.hpp"

namespace glRender
{

class Texture
{
public:
    Texture(const char * pathToFile);
    ~Texture();

        uint32_t id();

protected:
        uint32_t m_id;

};

}

#endif /* __TEXTURE_HPP__ */
