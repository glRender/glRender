#pragma once

#include "base.h"

namespace glRender
{

class Texture;

class Textures
{
public:
    Textures();
    Texture & operator = (const Texture &) = delete;
    ~Textures();

    void setTexture(const char * uniformName, std::shared_ptr<Texture> texture);

    Texture * texture(const uint32_t index) const;
    Texture * texture(const char * uniformName) const;
    bool isExistTexture(const uint32_t index) const;
    bool isExistTexture(const char * uniformName) const;
    const char * textureUniformName(const uint32_t index) const;

    inline int size() const
    {
        return m_textures.size();
    }

    inline bool isEmpty() const
    {
        return m_isEmpty;
    }

protected:
    std::map<const std::string, Texture *> m_textures;
    std::list<std::shared_ptr<Texture>> m_sharedPtrs;
    bool m_isEmpty = true;

};

}
