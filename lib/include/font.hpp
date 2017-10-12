#pragma once

#include "base.h"

namespace glRender
{

class Texture;
class ShaderProgram;
class Model;
class Camera;

namespace Font
{
    struct GlyphsInformation;

    class Font
    {
    public:
        Font(std::shared_ptr<Texture> texture, std::shared_ptr<GlyphsInformation> information);
        void setMaxTextLength(uint maxLength);
        uint maxTextLength() const;
        const char * uuid() const;
        void setText(std::wstring& text);
        void setShaderProgramUniforms();

        std::shared_ptr<ShaderProgram> shaderProgram() const;
        std::shared_ptr<Texture> texture() const;
        std::shared_ptr<GlyphsInformation> glyphsInfo() const;

        std::vector<int> utf8ToFontCodes(std::wstring & text);
        std::wstring fontCodesToUtf8(std::vector<int> & codes);

        std::vector<int> m_fontCodesText;
    private:
        void createShaderProgram();

    private:
        std::shared_ptr<ShaderProgram> m_shaderProgram;
        std::shared_ptr<Texture> m_texture;
        std::shared_ptr<GlyphsInformation> m_information;
        uint m_maxTextLength = 16;
//        std::wstring m_wstringText;

        std::string m_vertexShaderCode =
        "\n\
            #version 330 core \n\
            uniform mat4 model; \n\
            uniform mat4 view; \n\
            uniform mat4 projection; \n\
            layout (location = 0) in vec3 vertex; \n\
            layout (location = 1) in vec2 uv; \n\
            out vec2 keyring_uv; \n\
            void main(void) \n\
            { \n\
                keyring_uv = uv; \n\
                gl_Position      = projection * view * model * vec4 ( vertex, 1.0 ); \n\
            }\n\
        ";

        std::string m_fragmentShaderCode =
        " \n\
        #version 330 core \n\
        out vec4 color; \n\
        in vec2 keyring_uv; \n\
        uniform sampler2D texture0; \n\
        uniform vec2 glyphPos[$dictSize]; \n\
        uniform vec2 glyphSize[$dictSize]; \n\
        uniform vec2 glyphOffset[$dictSize]; \n\
        uniform int text[$maxTextLength]; \n\
        vec4 charFrag(int c, vec2 fragCoord) { \n\
            vec2 charCoord = glyphPos[c] + fragCoord;\n\
            charCoord.y -= glyphOffset[c].y;\n\
            return texture(texture0, charCoord); \n\
        } \n\
        vec4 drawText(vec2 pos, int text[$maxTextLength], vec2 fragCoord) {\n\
            vec4 fragColor = vec4(fragCoord, 1.0, 0.0); \n\
            float l = 0.0;\n\
            for (int i=0; i<$maxTextLength; i++) {\n\
                if (text[i] == 84) {\n\
                    break; \n\
                } \n\
                vec2 size = glyphSize[text[i]]; \n\
                vec2 offset = glyphOffset[text[i]]; \n\
                float left = l + pos.x; \n\
                float right = left + size.x; \n\
                float top = pos.y + offset.y;\n\
                float bottom = top + size.y;\n\
                if (fragCoord.x >= left && fragCoord.x < right) {\n\
                    if (fragCoord.y >= top && fragCoord.y < bottom) {\n\
                        vec2 charCoord; \n\
                        charCoord.x = (fragCoord.x - left); \n\
                        charCoord.y = (fragCoord.y - pos.y); \n\
                        fragColor = charFrag(text[i], charCoord); \n\
                    } \n\
                } \n\
                l = l + size.x; \n\
            } \n\
            return fragColor; \n\
        } \n\
         \n\
        void main(void) { \n\
            color = vec4(keyring_uv, 1.0, 0.0); \n\
            int text1[$maxTextLength]; \n\
//            text1[0] = 0; \n\
//            text1[1] = 1; \n\
//            text1[2] = 2; \n\
//            text1[3] = 3; \n\
//            text1[4] = 4; \n\
//            text1[5] = 5; \n\
//            text1[6] = 10; \n\
//            dict[104] = Char(vec2(0.169921875, 0.609375), vec2(0.041015625, 0.13671875), vec2(0.005859375, 0.04296875));\n\
//            dict[101] = Char(vec2(0.044921875, 0.21875), vec2(0.048828125, 0.10546875), vec2(0.001953125, 0.078125));\n\
//            dict[108] = Char(vec2(0.099609375, 0.609375), vec2(0.009765625, 0.13671875), vec2(0.005859375, 0.04296875));\n\
            color = drawText(vec2(0.1, 0.5), text, keyring_uv); \n\
        } \n\
        ";

    };

    std::shared_ptr<Font> createFromFile(const char * pathToFile);

}
}
