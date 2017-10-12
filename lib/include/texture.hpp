#ifndef __TEXTURE_HPP__		
#define __TEXTURE_HPP__

#include "base.h"
#include "image.hpp"
#include "vec2.hpp"

namespace glRender
{

class Texture
{
public:    
    enum class PixelFormat
    {        
        RGB,
        RGBA,
        No
    };

//    Texture(const char * pathToFile);
    Texture();
    Texture & operator = (const Texture & texture) = delete;
    ~Texture();

    void fillBy(uint width, uint height, PixelFormat format, void * data);

    uint width() const;
    uint heigth() const;

    const Vec2 & size() const;

    PixelFormat format() const;

    inline uint32_t id()
    {
        return m_id;
    }

private:
    uint m_id = -1;
    Vec2 m_size;
    PixelFormat m_pixelFormat = PixelFormat::No;
};

using TexturePtr = std::shared_ptr<Texture>;

std::shared_ptr<Texture> createTextureFromFile(const char * pathToFile);

}

#endif /* __TEXTURE_HPP__ */
