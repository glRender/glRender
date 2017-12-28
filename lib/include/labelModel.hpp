#pragma once

#include "base.h"
#include "model.hpp"

namespace glRender
{
    namespace Font {
        class Font;
    }

    class LabelModel : public Model
    {
    public:
        LabelModel(std::shared_ptr<Font::Font> font, const std::string & text);
        virtual ~LabelModel();
        void draw(Camera * camera) override;
        void setText(const std::string & text);
    private:
        void createGeometry(std::shared_ptr<Font::Font> font);
        void extractTextures(std::shared_ptr<Font::Font> font);
        void extractShaderProgram(std::shared_ptr<Font::Font> font);
    private:
        std::shared_ptr<Font::Font> m_font;
        std::wstring m_text;
    };

}
