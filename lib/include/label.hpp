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
        Label(const char * text, std::shared_ptr<Font::Font> font, uint maxTextLength = 255);
        virtual ~Label();
        void draw(Camera * camera) override;
        void setText(const char * text);
        const char * text() const;
    private:
        void createGeometry(std::shared_ptr<Font::Font> font);
        void extractTextures(std::shared_ptr<Font::Font> font);
        void extractShaderProgram(std::shared_ptr<Font::Font> font);
    private:
        std::wstring m_text;
        std::shared_ptr<Font::Font> m_font;
    };

}
