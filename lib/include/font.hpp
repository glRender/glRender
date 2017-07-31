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
    class GlyphsInformation;

    class Font
    {
    public:
        Font(std::shared_ptr<Texture> texture, std::shared_ptr<GlyphsInformation> information, uint maxLength = 255);
        void setMaxTextLength(uint maxLength);
        uint maxTextLength() const;
        const char * uuid() const;
        void setText(const char* text);

        std::shared_ptr<ShaderProgram> shaderProgram() const;
        std::shared_ptr<Texture> texture() const;
        std::shared_ptr<GlyphsInformation> glyphsInfo() const;

    private:
        void createShaderProgram();

    private:
        std::shared_ptr<ShaderProgram> m_shaderProgram;
        std::shared_ptr<Texture> m_texture;
        std::shared_ptr<GlyphsInformation> m_information;
        uint m_maxTextLength;

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
        uniform int text[$maxTextLength]; \n\
        struct Char {\n\
            vec2 pos;\n\
            vec2 size;\n\
        };\n\
        uniform Char dict[$dictSize]; \n\
        vec4 charFrag(int c, vec2 fragCoord) { \n\
            return texture(texture0, dict[c].pos + fragCoord); \n\
        } \n\
        vec4 drawText(vec2 pos, int text[$maxTextLength], vec2 fragCoord) {\n\
            vec4 fragColor = vec4(fragCoord, 1.0, 1.0); \n\
            float l = 0.0;\n\
            for (int i=0; i<$maxTextLength; i++) {\n\
                if (text[i] == 64) {\n\
                    break; \n\
                } \n\
                vec2 size = dict[text[i]].size; \n\
                float left = pos.x + (size.x * float(i)); \n\
                float right = pos.x + (size.x * (float(i) + 1.0)); \n\
                //float left = l + pos.x; \n\
                //float right = left + size.x; \n\
                if (fragCoord.x >= left && fragCoord.x < right) {\n\
                    if (fragCoord.y >= pos.y && fragCoord.y < pos.y + size.y) {\n\
                        vec2 charCoord; \n\
                        charCoord.x = (fragCoord.x - pos.x) - size.x * float(i); \n\
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
            color = vec4(keyring_uv, 1.0, 1.0); \n\
            color = drawText(vec2(0.1, 0.5), text, keyring_uv); \n\
        } \n\
        ";

    };

    std::shared_ptr<Font> createFromFile(const char * pathToFile, uint maxLength = 255);

}
}
