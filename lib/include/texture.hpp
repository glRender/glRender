#pragma once

#include "base.h"

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

    Texture();
    Texture & operator = (const Texture & texture) = delete;
    ~Texture();

    void fillBy(uint width, uint height, PixelFormat format, void * data);

    uint32_t id();

private:
    uint32_t m_id;

};

using TexturePtr = std::shared_ptr<Texture>;

std::shared_ptr<Texture> createTextureFromFile(const char * pathToFile);

}
