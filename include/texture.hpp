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

        uint id();

protected:
        uint m_id;

};

}

#endif /* __TEXTURE_HPP__ */
