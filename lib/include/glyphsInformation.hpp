#pragma once

#include "base.h"
#include "vec2.hpp"

namespace glRender
{
    class Vec2;
    namespace Font
    {
        struct GlyphInformation
        {
            uint code;
            Vec2 pos;
            Vec2 size;
            Vec2 offset;
            Vec2 origSize;
            std::unordered_map<uint, uint> keyring;

            void normalizeBySize(const Vec2& size);
        };

        struct GlyphsInformation
        {
            std::string fontName;
            std::string fontSize;
            std::string textureFileName;
            std::map<uint, GlyphInformation> map;

            std::string uuid() const;

            void normalizeBySize(const Vec2& size);
            static std::shared_ptr<GlyphsInformation> createFromFile(const char * pathToFile);
        };

    }
}
