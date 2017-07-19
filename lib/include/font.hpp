#pragma once

#include "base.h"

namespace glRender {

class Texture;
class ShaderProgram;

struct Char
{
    uint code;
    uint width;
    uint height;
    std::unordered_map<uint, uint> keyring;
};

struct TextureFontInformation
{
    std::unordered_map<uint, Char> map;
};

class Font
{
public:
    Font(std::shared_ptr<Texture> texture, const TextureFontInformation & information);
    Font(const char * pathToTexture, const char * pathToTextureFontInfo);

private:
    /*TODO Find way to make uuid be a real UUID*/
    const char * uuid;
    std::shared_ptr<Texture> m_texture;
    TextureFontInformation m_information;
    std::shared_ptr<ShaderProgram> m_shaderProgram;

    std::string m_vertexShaderText = "";
    std::string m_fragmentShaderText = "";

};

}
