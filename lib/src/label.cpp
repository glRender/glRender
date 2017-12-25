#include "label.hpp"
#include "font.hpp"
#include "geometryHelper.hpp"
#include "textures.hpp"
#include "texture.hpp"

using namespace glRender;

Label::Label(std::shared_ptr<Font::Font> font, const std::string & text)
    : m_font(font)
{
    setText(text);
    extractTextures(font);
    extractShaderProgram(font);
    createGeometry(font);
}

Label::~Label()
{

}

void Label::draw(Camera *camera)
{
    m_font->setText(m_text);
    Model::draw(camera);
}

void Label::setText(const std::string & text)
{
    m_text = utf8_to_wstring(text + "@");
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
