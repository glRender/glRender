#include "label.hpp"
#include "font.hpp"
#include "geometryHelper.hpp"

using namespace glRender;

Label::Label(const char * text, std::shared_ptr<Font::Font> font, uint maxTextLength)
    : m_font(font)
{
    m_font->setMaxTextLength(maxTextLength);

    extractTextures(font);
    extractShaderProgram(font);
    createGeometry(font);

    setText(text);

    setOrigin(0.0, 0.0, 0.0);
//    setWireframeMode(true);
}

Label::~Label()
{

}

void Label::draw(Camera *camera)
{
    shaderProgram()->fillUniformByArray<int>("text", (int*)m_text.c_str(), m_font->maxTextLength());
    Model::draw(camera);
}

void Label::setText(const char* text)
{
    m_text = utf8_to_wstring(text);
}

const char* Label::text() const
{
    return wstring_to_utf8(m_text).c_str();
}

void Label::extractTextures(std::shared_ptr<Font::Font> font)
{
    std::shared_ptr<Texture> texture = font->texture();
    Textures * textures = new Textures();
    textures->setTexture("texture0", texture);
    setTextures(textures);
}

void Label::createGeometry(std::shared_ptr<Font::Font> font)
{
    auto texture = font->texture();
    float ratioX = float(texture->width()) / texture->heigth();
    float ratioY = float(texture->heigth()) / texture->width();
    float scale = 10;
    std::shared_ptr<Geometry> geometry = GeometryHelper::Plane(Vec3(0, 0, -5.0),               Vec3(scale * ratioX, 0, -5.0),
                                                               Vec3(0, -scale * ratioY, -5.0), Vec3(scale * ratioX, -scale * ratioY, -5.0));
    setGeometry(geometry);
}

void Label::extractShaderProgram(std::shared_ptr<Font::Font> font)
{
    std::shared_ptr<ShaderProgram> shaderProgram = font->shaderProgram();
    setShaderProgram(shaderProgram);
}
