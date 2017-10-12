#pragma once

#include "base.h"
#include "model.hpp"

namespace glRender
{
    namespace Font {
        class Font;
    }

    class Label : public Model
    {
    public:
        Label(std::wstring& text, std::shared_ptr<Font::Font> font);
        virtual ~Label();
        void draw(Camera * camera) override;
        void setText(std::wstring& text);
    private:
        void createGeometry(std::shared_ptr<Font::Font> font);
        void extractTextures(std::shared_ptr<Font::Font> font);
        void extractShaderProgram(std::shared_ptr<Font::Font> font);
    private:
        std::shared_ptr<Font::Font> m_font;
        std::wstring m_text;
    };

}
