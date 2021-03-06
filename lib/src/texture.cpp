#include "texture.hpp"

#include "opengl.h"
#include "image.hpp"

namespace glRender
{

Texture::Texture()
{    
    glGenTextures(1, &m_id);

    glBindTexture(GL_TEXTURE_2D, m_id);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	// Set texture wrapping to GL_REPEAT
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glBindTexture(GL_TEXTURE_2D, 0);
}

Texture::~Texture()
{
    glDeleteTextures(1, &m_id);
}

void Texture::fillBy(uint width, uint height, Texture::PixelFormat format, void *data)
{
    GLint pixelFormat = GL_RGB;
    if (format == Texture::PixelFormat::RGBA)
    {
        pixelFormat = GL_RGBA;
    }

    glBindTexture(GL_TEXTURE_2D, m_id);
    glTexImage2D(GL_TEXTURE_2D, 0, pixelFormat, width, height, 0, pixelFormat, GL_UNSIGNED_BYTE, data);
    glBindTexture(GL_TEXTURE_2D, 0);

    m_size.set(width, height);
    m_pixelFormat = format;
}

uint Texture::width() const
{
    return m_size.x;
}

uint Texture::heigth() const
{
    return m_size.y;
}

const Vec2& Texture::size() const
{
    return m_size;
}

Texture::PixelFormat Texture::format() const
{
    return m_pixelFormat;
}

uint Texture::id() const
{
    return m_id;
}

std::shared_ptr<Texture> createTextureFromFile(const char * pathToFile)
{
    std::shared_ptr<Texture> texture = std::make_shared<Texture>();

    Image * image = new Image(pathToFile);

    if( image->isLoaded() )
    {
        Texture::PixelFormat pixelFormat = Texture::PixelFormat::RGB;
        if( image->components() == 4)
        {
            pixelFormat = Texture::PixelFormat::RGBA;
        }

        texture->fillBy(image->width(), image->height(), pixelFormat, image->data());

        image->clear();
        delete image;
        return texture;
    }
    else
    {
        throw std::invalid_argument("Failed to load image: " + patch::to_string(pathToFile));
    }
}

}
