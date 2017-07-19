#ifndef __TEXTURE_HPP__		
#define __TEXTURE_HPP__

#include "base.h"
#include "image.hpp"

namespace glRender
{

class Texture
{
public:
    enum class PixelFormat
    {
        RGB,
        RGBA
    };

//    Texture(const char * pathToFile);
    Texture();
    Texture & operator = (const Texture & texture) = delete;
    ~Texture();

    void fillBy(uint width, uint height, PixelFormat format, void * data);

    inline uint32_t id()
    {
        return m_id;
    }

protected:
    uint32_t m_id;

};

std::shared_ptr<Texture> createTextureFromFile(const char * pathToFile);

}

#endif /* __TEXTURE_HPP__ */
