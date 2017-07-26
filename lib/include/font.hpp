#pragma once

#include "base.h"

namespace glRender
{

class Texture;
class ShaderProgram;
class Model;

namespace Font
{
    namespace Glyphs
    {
        class Information;
    }

    class Font
    {
    public:
        Font(std::shared_ptr<Texture> texture, std::shared_ptr<Glyphs::Information> information);

    private:
        /*TODO Find way to make uuid be a real UUID*/
    //    long long uuid;
        std::shared_ptr<Texture> m_texture;
        std::shared_ptr<ShaderProgram> m_shaderProgram;
        std::shared_ptr<Glyphs::Information> m_information;

        Model * m_model = nullptr;

        std::string m_vertexShaderCode =
        "\n\
            #version 330 core \n\
            uniform mat4 model; \n\
            uniform mat4 view; \n\
            uniform mat4 projection; \n\
            layout (location = 0) in vec3 vertex; \n\
            void main(void) \n\
            { \n\
               gl_Position      = projection * view * model * vec4 ( vertex, 1.0 ); \n\
            }\n\
        ";

        std::string m_fragmentShaderCode =
        " \n\
            #version 330 core \n\
            out vec4 color; \n\
            void main(void) \n\
            { \n\
                color = vec4(0.0, 0.0, 0.0, 1.0); \n\
            } \n\
        ";

    };
}
}
