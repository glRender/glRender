#include "font.hpp"

#include "shader.hpp"
#include "shaderProgram.hpp"
#include "texture.hpp"
#include "resourceManager.hpp"
#include "geometryHelper.hpp"
#include "model.hpp"
#include "camera.hpp"
#include "glyphsInformation.hpp"

namespace glRender
{

namespace Font
{

Font::Font(std::shared_ptr<Texture> texture, std::shared_ptr<GlyphsInformation> information, uint maxLength)
    : m_texture(texture)
    , m_information(information)
    , m_maxTextLength(maxLength)
{
    createShaderProgram();

    //0.908203125, 0.53125
//    shaderProgram()->fillUniformByArray<int>("dict[0].pos.x", (int*)m_text.c_str(), 3);
//    Vec2 pos(0.908203125, 0.53125);
//    Vec2 size(0.08984375, 0.1796875);
//    shaderProgram()->setUniform<Vec2>("dict[64].pos", pos);
//    shaderProgram()->setUniform<Vec2>("dict[64].size", size);

    for (auto & i : information->map)
    {
        std::string fieldPos = std::string("dict[") + patch::to_string(i.first) + std::string("].pos");
        std::string fieldSize = std::string("dict[") + patch::to_string(i.first) + std::string("].size");

        shaderProgram()->setUniform<Vec2>(fieldPos.c_str(), i.second.pos);
        shaderProgram()->setUniform<Vec2>(fieldSize.c_str(), i.second.size);
    }

}

void Font::setMaxTextLength(uint maxLength)
{
    if (m_maxTextLength != maxLength)
    {
        m_maxTextLength = maxLength;
        createShaderProgram();
    }
}

uint Font::maxTextLength() const
{
    return m_maxTextLength;
}

const char* Font::uuid() const
{
    std::string uuid = m_information->uuid() + "_" + patch::to_string(m_maxTextLength);
    return uuid.c_str();
}

std::shared_ptr<ShaderProgram> Font::shaderProgram() const
{
    return m_shaderProgram;
}

std::shared_ptr<Texture> Font::texture() const
{
    return m_texture;
}

std::shared_ptr<GlyphsInformation> Font::glyphsInfo() const
{
    return m_information;
}

void Font::createShaderProgram()
{
    ResourceManager::instance().shaderPrograms().create(uuid(), [this]() {
        std::string maxTextLength = patch::to_string(m_maxTextLength);
        std::string dictSize = patch::to_string(/*m_information->map.size()*/250);

        std::string vertexShaderCode(m_vertexShaderCode);
        std::string fragmentShaderCode(m_fragmentShaderCode);

        replaceAll(fragmentShaderCode, "$maxTextLength", maxTextLength);
        replaceAll(fragmentShaderCode, "$dictSize", dictSize);

        std::map<ShaderType, const char *> shadersTexts = {
            {ShaderType::VertexShader, vertexShaderCode.c_str()},
            {ShaderType::FragmentShader, fragmentShaderCode.c_str()}
        };
        auto shaderProgram = createShaderProgramFromText(shadersTexts);
        shaderProgram->addAttribute<Vec3>("vertex");
        shaderProgram->addAttribute<Vec2>("uv");

        shaderProgram->addUniform<Mat4>("projection");
        shaderProgram->addUniform<Mat4>("view");
        shaderProgram->addUniform<Mat4>("model");
        shaderProgram->addUniform<Texture>("texture0");
        shaderProgram->addUniform<int>("text");

//        for (auto & i : m_information->map)
//        {
//            std::string fieldPos = std::string("dict[") + patch::to_string(i.first) + std::string("].pos");
//            std::string fieldSize = std::string("dict[") + patch::to_string(i.first) + std::string("].size");

//            shaderProgram->addUniform<void>(fieldPos.c_str());
//            shaderProgram->addUniform<void>(fieldSize.c_str());

//        }

        std::string fieldPos = std::string("dict[") + patch::to_string(64) + std::string("].pos");
        std::string fieldSize = std::string("dict[") + patch::to_string(64) + std::string("].size");

        shaderProgram->addUniform<void>(fieldPos.c_str());
        shaderProgram->addUniform<void>(fieldSize.c_str());


        return shaderProgram;
    });
    m_shaderProgram = ResourceManager::instance().shaderPrograms().get(uuid());
}

std::shared_ptr<Font> createFromFile(const char * pathToFile, uint maxLength)
{
    std::shared_ptr<GlyphsInformation> info = GlyphsInformation::createFromFile(pathToFile);

    std::string uuid = info->uuid();

    ResourceManager::instance().textures().create(uuid.c_str(), [&info]() {
        return createTextureFromFile(info->textureFileName.c_str());
    });
    std::shared_ptr<Texture> texture = ResourceManager::instance().textures().get(uuid.c_str());
    info->normalizeBySize(Vec2(texture->width(), texture->heigth()));

    return std::make_shared<Font>(texture, info, maxLength);
}

}
}
