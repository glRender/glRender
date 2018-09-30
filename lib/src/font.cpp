#include "font.hpp"

#include "shader.hpp"
#include "shaderProgram.hpp"
#include "texture.hpp"
#include "textures.hpp"
#include "resourceManager.hpp"
#include "geometryHelper.hpp"
#include "model.hpp"
#include "camera.hpp"
#include "glyphsInformation.hpp"

//#include <chrono>
//#include <thread>

namespace glRender
{

namespace Font
{

Font::Font(std::shared_ptr<Texture> texture, std::shared_ptr<GlyphsInformation> information)
    : m_texture(texture)
    , m_information(information)
{
    createShaderProgram();

    //0.908203125, 0.53125
//    shaderProgram()->fillUniformByArray<int>("dict[0].pos.x", (int*)m_text.c_str(), 3);
//    Vec2 pos(0.908203125, 0.53125);
//    Vec2 size(0.08984375, 0.1796875);
//    shaderProgram()->setUniform<Vec2>("dict[64].pos", pos);
//    shaderProgram()->setUniform<Vec2>("dict[64].size", size);
//    shaderProgram()->setUniform<Vec2>("dict[64].offset", offset);

//    std::string fieldPos;
//    std::string fieldSize;
//    std::string fieldOffset;

//    for (std::pair<uint, GlyphInformation> i : m_information->fontCodes)
//    {

//        fieldPos = std::string("dict[") + patch::to_string(i.first) + std::string("].pos");
//        fieldSize = std::string("dict[") + patch::to_string(i.first) + std::string("].size");
//        fieldOffset = std::string("dict[") + patch::to_string(i.first) + std::string("].offset");

//        std::cout << i.first << i.second.pos << i.second.size << i.second.offset << std::endl;

////        m_shaderProgram->addUniform<Vec2>(fieldPos.c_str());
//        m_shaderProgram->setUniform<Vec2>(fieldPos.c_str(), i.second.pos);
//        m_shaderProgram->addUniform<Vec2>(fieldSize.c_str());
//        m_shaderProgram->setUniform<Vec2>(fieldSize.c_str(), i.second.size);

//        m_shaderProgram->addUniform<Vec2>(fieldOffset.c_str());
//        m_shaderProgram->setUniform<Vec2>(fieldOffset.c_str(), i.second.offset);
//    }
//    shaderProgram()->fillUniformByArray<int>("text", m_intPtrText, m_sizeOfText);
//    const Vec2 * data = m_information->glyphPos.data();

    m_shaderProgram->fillUniformByArray("glyphPos", m_information->glyphPos.data(), m_information->glyphPos.size());
    m_shaderProgram->fillUniformByArray("glyphSize", m_information->glyphSize.data(), m_information->glyphSize.size());
    m_shaderProgram->fillUniformByArray("glyphOffset", m_information->glyphOffset.data(), m_information->glyphOffset.size());
    m_shaderProgram->fillUniformByArray("text", m_fontCodesText.data(), m_fontCodesText.size());
}

void Font::setMaxTextLength(uint maxLength)
{
    if (m_maxTextLength != maxLength)
    {
        m_maxTextLength = maxLength;
        createShaderProgram();
    }
}

void Font::setText(std::wstring& text)
{
//    std::cout << m_maxTextLength << ", " << text.size() << std::endl;
//    if (m_maxTextLength < text.size())
//    {
//        std::cout << "max text length: " << text.size() << std::endl;
//        setMaxTextLength(text.size());
//    }

//    m_wstringText = text;
    m_fontCodesText = utf8ToFontCodes(text);
    m_shaderProgram->fillUniformByArray<int>("text", m_fontCodesText.data(), m_fontCodesText.size());
}

uint Font::maxTextLength() const
{
    return m_maxTextLength;
}

const char* Font::uuid() const
{
    std::string uuid = m_information->uuid() + "_" + patch::to_string(m_maxTextLength);
    std::cout << uuid.c_str() << std::endl;
    return uuid.c_str();
}

std::vector<int> Font::utf8ToFontCodes(std::wstring& text)
{
    std::vector<int> fontCodes;

    for (auto i : text)
    {
        fontCodes.push_back(m_information->utf8CodeToFontCode[i]);
    }
    return fontCodes;
}

std::wstring Font::fontCodesToUtf8(std::vector<int> &fontCodes)
{
    std::wstring utf8Text = L"";

    for (auto i : fontCodes)
    {
        wchar_t c(m_information->fontCodeToUtf8Code[i]);
        utf8Text += c;
    }
    return utf8Text;
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
    const char * m_uuid = uuid();

    ResourceManager::instance().shaderPrograms().create(m_uuid, [this]() {
        std::string maxTextLength = patch::to_string(m_maxTextLength);
        std::string dictSize = patch::to_string(m_information->glyphPos.size());

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
        shaderProgram->addUniform<Vec2>("glyphPos");
        shaderProgram->addUniform<Vec2>("glyphSize");
        shaderProgram->addUniform<Vec2>("glyphOffset");

//        for (auto & i : m_information->fontCodes)
//        {
//            std::string fieldPos = std::string("dict[") + patch::to_string(i.first) + std::string("].pos");
//            std::string fieldSize = std::string("dict[") + patch::to_string(i.first) + std::string("].size");
//            std::string fieldOffset = std::string("dict[") + patch::to_string(i.first) + std::string("].offset");

//            shaderProgram->addUniform<Vec2>(fieldPos.c_str());
//            shaderProgram->addUniform<Vec2>(fieldSize.c_str());
//            shaderProgram->addUniform<Vec2>(fieldOffset.c_str());

//        }

//        std::string fieldPos = std::string("dict[") + patch::to_string(0) + std::string("].pos");
//        std::string fieldSize = std::string("dict[") + patch::to_string(0) + std::string("].size");
//        std::string fieldOffset = std::string("dict[") + patch::to_string(0) + std::string("].offset");

//        shaderProgram->addUniform<Vec2>(fieldPos.c_str());
//        shaderProgram->addUniform<Vec2>(fieldSize.c_str());
//        shaderProgram->addUniform<Vec2>(fieldOffset.c_str());

        return shaderProgram;
    });
    m_shaderProgram = ResourceManager::instance().shaderPrograms().get(m_uuid);
}

std::shared_ptr<Font> createFromFile(const char * pathToFile)
{
    std::shared_ptr<GlyphsInformation> info = GlyphsInformation::createFromFile(pathToFile);

    std::string uuid = info->uuid();

    ResourceManager::instance().textures().create(uuid.c_str(), [&info]() {
        return createTextureFromFile(info->textureFileName.c_str());
    });
    std::shared_ptr<Texture> texture = ResourceManager::instance().textures().get(uuid.c_str());
    info->normalizeBySize(texture->size());

    return std::make_shared<Font>(texture, info);
}

}
}
