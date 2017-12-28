#pragma once

#include "base.h"
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

    Texture();
    Texture & operator = (const Texture & texture) = delete;
    ~Texture();

    void fillBy(uint width, uint height, PixelFormat format, void * data);
    uint width() const;
    uint heigth() const;
    const Vec2 & size() const;
    PixelFormat format() const;

    uint id() const;

private:
    uint m_id = -1;
    Vec2 m_size;
    PixelFormat m_pixelFormat = PixelFormat::No;

};

using TexturePtr = std::shared_ptr<Texture>;

std::shared_ptr<Texture> createTextureFromFile(const char * pathToFile);

}
